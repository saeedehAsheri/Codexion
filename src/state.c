#include "../includes/codexion.h"

int	simulation_is_finished(t_simulation *simulation)
{
	int	finished;

	pthread_mutex_lock(&simulation->state_mutex);
	finished = simulation->is_finished;
	pthread_mutex_unlock(&simulation->state_mutex);
	return (finished);
}

void	finish_simulation(t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->state_mutex);
	simulation->is_finished = 1;
	pthread_mutex_unlock(&simulation->state_mutex);
}