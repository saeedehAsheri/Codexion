#include "../includes/codexion.h"

static void	destroy_all_mutexes(t_dongle *dongles, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&dongles[i].dongle_mutex);
		i++;
	}
}

int	init_dongles(t_simulation *simulation)
{
	int	i;
	int	count;

	i = 0;
	count = simulation->config.number_of_coders;
	simulation->dongles = malloc(sizeof(t_dongle) * count);
	if (!simulation->dongles)
		return (0);
	while (i < count)
	{
		simulation->dongles[i].id = i + 1;
		simulation->dongles[i].available_at = 0;
		if (pthread_mutex_init(
				&simulation->dongles[i].dongle_mutex, NULL) != 0)
		{
			destroy_all_mutexes(simulation->dongles, i);
			free(simulation->dongles);
			simulation->dongles = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

int	lock_dongle(t_coder *coder, t_dongle *dongle)
{
	long	current_time;
	long	wait_time;

	while (!simulation_is_finished(coder->simulation))
	{
		pthread_mutex_lock(&dongle->dongle_mutex);
		current_time = get_time_ms();
		if (current_time >= dongle->available_at)
		{
			print_status(coder, "has taken a dongle");
			return (1);
		}
		wait_time = dongle->available_at - current_time;
		pthread_mutex_unlock(&dongle->dongle_mutex);
		if (wait_time > 0
			&& !interruptible_sleep(coder->simulation, wait_time))
			return (0);
	}
	return (0);
}

void	unlock_dongle(t_coder *coder, t_dongle *dongle)
{
	dongle->available_at = get_time_ms()
		+ coder->simulation->config.dongle_cooldown;
	pthread_mutex_unlock(&dongle->dongle_mutex);
}
