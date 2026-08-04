#include "../includes/codexion.h"

int	scheduler_push(t_simulation *simulation, t_request request)
{
	t_scheduler_queue	*queue;
	int					result;

	if (!simulation)
		return (0);
	queue = &simulation->scheduler_queue;
	pthread_mutex_lock(&queue->mutex);
	result = heap_push(simulation, request);
	if (result)
		pthread_cond_broadcast(&queue->condition);
	pthread_mutex_unlock(&queue->mutex);
	return (result);
}

int	scheduler_pop(t_simulation *simulation, t_request *request)
{
	t_scheduler_queue	*queue;
	int					result;

	if (!simulation || !request)
		return (0);
	queue = &simulation->scheduler_queue;
	pthread_mutex_lock(&queue->mutex);
	result = heap_pop(simulation, request);
	pthread_mutex_unlock(&queue->mutex);
	return (result);
}

void	scheduler_wake_all(t_simulation *simulation)
{
	t_scheduler_queue	*queue;

	if (!simulation)
		return ;
	queue = &simulation->scheduler_queue;
	pthread_mutex_lock(&queue->mutex);
	queue->busy = 0;
	pthread_cond_broadcast(&queue->condition);
	pthread_mutex_unlock(&queue->mutex);
}
void	scheduler_release(t_simulation *simulation)
{
	t_scheduler_queue	*queue;

	if (!simulation)
		return ;
	queue = &simulation->scheduler_queue;
	pthread_mutex_lock(&queue->mutex);
	queue->busy = 0;
	pthread_cond_broadcast(&queue->condition);
	pthread_mutex_unlock(&queue->mutex);
}

