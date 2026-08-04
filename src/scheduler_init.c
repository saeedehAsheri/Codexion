#include "../includes/codexion.h"

static void	reset_scheduler(t_scheduler_queue *queue)
{
	queue->heap = NULL;
	queue->size = 0;
	queue->capacity = 0;
	queue->mutex_initialized = 0;
	queue->condition_initialized = 0;
	queue->busy = 0;
}

void	destroy_scheduler(t_simulation *simulation)
{
	t_scheduler_queue	*queue;

	if (!simulation)
		return ;
	queue = &simulation->scheduler_queue;
	if (queue->condition_initialized)
	{
		pthread_cond_destroy(&queue->condition);
		queue->condition_initialized = 0;
	}
	if (queue->mutex_initialized)
	{
		pthread_mutex_destroy(&queue->mutex);
		queue->mutex_initialized = 0;
	}
	free(queue->heap);
	queue->heap = NULL;
	queue->size = 0;
	queue->capacity = 0;
	queue->busy = 0;
}

int	init_scheduler(t_simulation *simulation)
{
	t_scheduler_queue	*queue;
	int					count;

	if (!simulation)
		return (0);
	queue = &simulation->scheduler_queue;
	reset_scheduler(queue);
	count = simulation->config.number_of_coders;
	queue->heap = malloc(sizeof(t_request) * count);
	if (!queue->heap)
		return (0);
	queue->capacity = count;
	if (pthread_mutex_init(&queue->mutex, NULL) != 0)
	{
		free(queue->heap);
		queue->heap = NULL;
		return (0);
	}
	queue->mutex_initialized = 1;
	if (pthread_cond_init(&queue->condition, NULL) != 0)
	{
		destroy_scheduler(simulation);
		return (0);
	}
	queue->condition_initialized = 1;
	return (1);
}