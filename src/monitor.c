#include "../includes/codexion.h"

static int	coder_burned_out(t_coder *coder)
{
	long	last_start;
	long	elapsed;
	int		compile_count;
	int		required;

	pthread_mutex_lock(&coder->simulation->state_mutex);
	last_start = coder->last_compile_start;
	compile_count = coder->compile_count;
	pthread_mutex_unlock(&coder->simulation->state_mutex);
	required = coder->simulation->config.number_of_compiles_required;
	if (compile_count >= required)
		return (0);
	elapsed = get_time_ms() - last_start;
	return (elapsed >= coder->simulation->config.time_to_burnout);
}

static int	all_coders_finished(t_simulation *simulation)
{
	int	i;
	int	required;

	required = simulation->config.number_of_compiles_required;
	i = 0;
	while (i < simulation->config.number_of_coders)
	{
		if (get_compile_count(&simulation->coders[i]) < required)
			return (0);
		i++;
	}
	return (1);
}

static int	check_burnout(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->config.number_of_coders)
	{
		if (coder_burned_out(&simulation->coders[i]))
		{
			print_burnout(&simulation->coders[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_routine(void *argument)
{
	t_simulation	*simulation;

	simulation = (t_simulation *)argument;
	while (!simulation_is_finished(simulation))
	{
		if (check_burnout(simulation))
			return (NULL);
		if (all_coders_finished(simulation))
		{
			finish_simulation(simulation);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
