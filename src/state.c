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
	int	should_wake;

	if (!simulation)
		return ;
	should_wake = 0;
	pthread_mutex_lock(&simulation->state_mutex);
	if (!simulation->is_finished)
	{
		simulation->is_finished = 1;
		should_wake = 1;
	}
	pthread_mutex_unlock(&simulation->state_mutex);
	if (should_wake)
		scheduler_wake_all(simulation);
}
