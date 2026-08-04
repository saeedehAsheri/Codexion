#include "../includes/codexion.h"

static t_request	create_request(t_coder *coder)
{
	t_request	request;

	request.coder = coder;
	request.arrival_time = get_time_ms();
	request.deadline = get_last_compile_start(coder)
		+ coder->simulation->config.time_to_burnout;
	return (request);
}

static int	is_coder_at_top(t_scheduler_queue *queue, t_coder *coder)
{
	if (queue->size == 0)
		return (0);
	return (queue->heap[0].coder == coder);
}

static int	wait_until_allowed(t_coder *coder,
		t_scheduler_queue *queue)
{
	t_simulation	*simulation;

	simulation = coder->simulation;
	while ((!is_coder_at_top(queue, coder) || queue->busy)
		&& !simulation_is_finished(simulation))
		pthread_cond_wait(&queue->condition, &queue->mutex);
	if (simulation_is_finished(simulation))
		return (0);
	return (1);
}

int	scheduler_wait_turn(t_coder *coder)
{
	t_simulation			*simulation;
	t_scheduler_queue		*queue;
	t_request				request;

	if (!coder || !coder->simulation)
		return (0);
	simulation = coder->simulation;
	queue = &simulation->scheduler_queue;
	request = create_request(coder);
	pthread_mutex_lock(&queue->mutex);
	if (!heap_push(simulation, request))
	{
		pthread_mutex_unlock(&queue->mutex);
		return (0);
	}
	pthread_cond_broadcast(&queue->condition);
	if (!wait_until_allowed(coder, queue))
	{
		pthread_mutex_unlock(&queue->mutex);
		return (0);
	}
	queue->busy = 1;
	heap_pop(simulation, &request);
	pthread_mutex_unlock(&queue->mutex);
	return (1);
}
