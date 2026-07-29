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

int	init_simulation(t_config *input_config, t_simulation *init_values)
{
	if (!input_config || !init_values)
		return (0);
	init_values->coders = NULL;
	init_values->dongles = NULL;
	init_values->config = *input_config;
	init_values->is_finished = 0;
	init_values->start_time = 0;
	init_values->print_mutex_initialized = 0;
	if (!init_dongles(init_values))
		return (0);
	if (!init_coders(init_values))
	{
		cleanup_dongles(init_values);
		return (0);
	}
	if (pthread_mutex_init(&init_values->print_mutex, NULL) != 0)
	{
		free(init_values->coders);
		init_values->coders = NULL;
		cleanup_dongles(init_values);
		return (0);
	}
	init_values->print_mutex_initialized = 1;
	return (1);
}
