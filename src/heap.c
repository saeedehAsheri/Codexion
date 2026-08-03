#include "../includes/codexion.h"

int	heap_push(t_simulation *simulation, t_request request)
{
	t_scheduler_queue	*queue;
	int					index;

	if (!simulation)
		return (0);
	queue = &simulation->scheduler_queue;
	if (queue->size >= queue->capacity)
		return (0);
	index = queue->size;
	queue->heap[index] = request;
	queue->size++;
	heap_sift_up(simulation, index);
	return (1);
}

int	heap_pop(t_simulation *simulation, t_request *request)
{
	t_scheduler_queue	*queue;

	if (!simulation || !request)
		return (0);
	queue = &simulation->scheduler_queue;
	if (queue->size == 0)
		return (0);
	*request = queue->heap[0];
	queue->size--;
	if (queue->size > 0)
	{
		queue->heap[0] = queue->heap[queue->size];
		heap_sift_down(simulation, 0);
	}
	return (1);
}