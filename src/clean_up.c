#include "../includes/codexion.h"

void	free_simulation(t_simulation *simulation)
{
	int i;
	/*you should destroy the mutexes first*/
	if (!simulation)
		return ;

	if (simulation->dongles)
	{
		i = 0;
		while ( i < simulation->config.number_of_coders)
		{
			pthread_mutex_destroy(
				&simulation->dongles[i].dongle_mutex
			);
			i++;
		}
		free(simulation->dongles);
		simulation->dongles = NULL;
	}

	free(simulation->coders);
	simulation->coders = NULL;

}
