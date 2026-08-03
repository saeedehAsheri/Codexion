#include "../includes/codexion.h"

int	heap_has_priority(t_simulation *simulation,
		t_request *first, t_request *second)
{
	if (simulation->config.scheduler == FIFO)
	{
		if (first->arrival_time != second->arrival_time)
			return (first->arrival_time < second->arrival_time);
	}
	else if (first->deadline != second->deadline)
		return (first->deadline < second->deadline);
	return (first->coder->id < second->coder->id);
}

void	heap_swap(t_request *first, t_request *second)
{
	t_request	temp;

	temp = *first;
	*first = *second;
	*second = temp;
}

void	heap_sift_up(t_simulation *simulation, int index)
{
	t_scheduler_queue	*queue;
	int					parent;

	queue = &simulation->scheduler_queue;
	while (index > 0)
	{
		parent = (index - 1) / 2;
		if (!heap_has_priority(simulation,
				&queue->heap[index], &queue->heap[parent]))
			break ;
		heap_swap(&queue->heap[index], &queue->heap[parent]);
		index = parent;
	}
}

void	heap_sift_down(t_simulation *simulation, int index)
{
	t_scheduler_queue	*queue;
	int					left;
	int					right;
	int					best;

	queue = &simulation->scheduler_queue;
	while (1)
	{
		left = (2 * index) + 1;
		right = (2 * index) + 2;
		best = index;
		if (left < queue->size
			&& heap_has_priority(simulation,
				&queue->heap[left], &queue->heap[best]))
			best = left;
		if (right < queue->size
			&& heap_has_priority(simulation,
				&queue->heap[right], &queue->heap[best]))
			best = right;
		if (best == index)
			break ;
		heap_swap(&queue->heap[index], &queue->heap[best]);
		index = best;
	}
}
