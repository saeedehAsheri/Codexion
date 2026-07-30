#include "../includes/codexion.h"

static void	join_created_threads(t_simulation *simulation, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(simulation->coders[i].thread_id, NULL);
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
