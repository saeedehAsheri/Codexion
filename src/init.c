#include "../includes/codexion.h"

int	init_simulation(t_config *input_config, t_simulation *init_values)
{
	if (!input_config || !init_values)
		return (0);
	init_values->coders = NULL;
	init_values->dongles = NULL;
	init_values->config = *input_config;
	init_values->is_finished = 0;
	init_values->start_time = 0;
	if (!init_dongles(init_values))
		return (0);
	if (!init_coders(init_values))
	{
		free(init_values->dongles);
		init_values->dongles = NULL;
		return (0);
	}
	return (1);
}
