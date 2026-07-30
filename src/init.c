#include "../includes/codexion.h"

static void	init_simulation_values(t_config *config,
		t_simulation *simulation)
{
	simulation->config = *config;
	simulation->coders = NULL;
	simulation->dongles = NULL;
	simulation->start_time = 0;
	simulation->is_finished = 0;
	simulation->print_mutex_initialized = 0;
	simulation->state_mutex_initialized = 0;
}

static int	init_simulation_mutexes(t_simulation *simulation)
{
	if (pthread_mutex_init(&simulation->print_mutex, NULL) != 0)
		return (0);
	simulation->print_mutex_initialized = 1;
	if (pthread_mutex_init(&simulation->state_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&simulation->print_mutex);
		simulation->print_mutex_initialized = 0;
		return (0);
	}
	simulation->state_mutex_initialized = 1;
	return (1);
}

int	init_simulation(t_config *config, t_simulation *simulation)
{
	if (!config || !simulation)
		return (0);
	init_simulation_values(config, simulation);
	if (!init_dongles(simulation))
		return (0);
	if (!init_coders(simulation))
	{
		cleanup_dongles(simulation);
		return (0);
	}
	if (!init_simulation_mutexes(simulation))
	{
		free(simulation->coders);
		simulation->coders = NULL;
		cleanup_dongles(simulation);
		return (0);
	}
	return (1);
}
