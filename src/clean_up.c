#include "../includes/codexion.h"

void	cleanup_dongles(t_simulation *simulation)
{
	int	i;

	if (!simulation || !simulation->dongles)
		return ;
	i = 0;
	while (i < simulation->config.number_of_coders)
	{
		pthread_mutex_destroy(
			&simulation->dongles[i].dongle_mutex);
		i++;
	}
	free(simulation->dongles);
	simulation->dongles = NULL;
}

void	free_simulation(t_simulation *simulation)
{
	if (!simulation)
		return ;
	if (simulation->state_mutex_initialized)
	{
		pthread_mutex_destroy(&simulation->state_mutex);
		simulation->state_mutex_initialized = 0;
	}
	if (simulation->print_mutex_initialized)
	{
		pthread_mutex_destroy(&simulation->print_mutex);
		simulation->print_mutex_initialized = 0;
	}
	cleanup_dongles(simulation);
	free(simulation->coders);
	simulation->coders = NULL;
}
