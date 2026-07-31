#include "../includes/codexion.h"

static void	join_created_threads(t_simulation *simulation, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(simulation->coders[i].thread_id, NULL);
		pthread_join(simulation->monitor_thread, NULL);
		i++;
	}
}

int	create_threads(t_simulation *simulation)
{
	int	count;
	int	i;

	if (!simulation || !simulation->coders)
		return (0);
	count = simulation->config.number_of_coders;
	i = 0;
	while (i < count)
	{
		if (pthread_create(&simulation->coders[i].thread_id,
				NULL, coder_routine, &simulation->coders[i]) != 0)
		{
			finish_simulation(simulation);
			join_created_threads(simulation, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_threads(t_simulation *simulation)
{
	int	count;
	int	i;

	if (!simulation || !simulation->coders)
		return (0);
	count = simulation->config.number_of_coders;
	i = 0;
	while (i < count)
	{
		if (pthread_join(simulation->coders[i].thread_id, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	join_monitor_thread(t_simulation *simulation)
{
	if (!simulation || !simulation->monitor_created)
		return (0);
	if (pthread_join(simulation->monitor_thread, NULL) != 0)
		return (0);
	simulation->monitor_created = 0;
	return (1);
}

int	create_monitor_thread(t_simulation *simulation)
{
	if (!simulation)
		return (0);
	if (pthread_create(&simulation->monitor_thread,
			NULL, monitor_routine, simulation) != 0)
		return (0);
	simulation->monitor_created = 1;
	return (1);
}
