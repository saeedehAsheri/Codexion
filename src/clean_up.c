#include "../includes/codexion.h"

void	free_simulation(t_simulation *simulation)
{
	/*you should destroy the mutexes first*/
	if (!simulation)
		return ;
	if (simulation->coders)
	{
		free(simulation->coders);
		simulation->coders = NULL;
	}
	if (simulation->dongles)
	{
		free(simulation->dongles);
		simulation->dongles = NULL;
	}
}
