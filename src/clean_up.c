#include "../includes/codexion.h"

void	free_simulation(t_simulation *simulation)
{
	int	i;

	if (!simulation)
		return ;
	if (simulation->print_mutex_initialized)
	{
		pthread_mutex_destroy(&simulation->print_mutex);
		simulation->print_mutex_initialized = 0;
	}
	if (simulation->dongles)
	{
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

	free(simulation->coders);
	simulation->coders = NULL;
	
}
