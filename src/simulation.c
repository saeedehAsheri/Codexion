#include "../includes/codexion.h"

static void	sleep_ms(int milliseconds)
{
	usleep((unsigned int)milliseconds * 1000);
}

static void	print_status(t_coder *coder, const char *message)
{
	long	timestamp;

    pthread_mutex_lock(&coder->simulation->print_mutex);
	timestamp = get_time_ms() - coder->simulation->start_time;
	printf("%ld %d %s\n", timestamp, coder->id, message);
    pthread_mutex_unlock(&coder->simulation->print_mutex);
}

static void	lock_dongle(t_coder *coder, t_dongle *dongle)
{
	long	wait_time;

	while (1)
	{
		pthread_mutex_lock(&dongle->dongle_mutex);
		if (get_time_ms() >= dongle->available_at)
		{
			//dongle->is_available = 0;
			print_status(coder, "has taken a dongle");
			return ;
		}
		wait_time = dongle->available_at - get_time_ms();
		pthread_mutex_unlock(&dongle->dongle_mutex);
		if (wait_time > 0)
			usleep((unsigned int)wait_time * 1000);
	}
}

static void	unlock_dongle(t_coder *coder, t_dongle *dongle)
{
	dongle->available_at = get_time_ms()
		+ coder->simulation->config.dongle_cooldown;
	//dongle->is_available = 0;
	pthread_mutex_unlock(&dongle->dongle_mutex);
}

static void	run_compile(t_coder *coder)
{
	coder->last_compile_start = get_time_ms();
	print_status(coder, "is compiling");
	sleep_ms(coder->simulation->config.time_to_compile);
	coder->compile_count++;
}

static void	run_debug(t_coder *coder)
{
	print_status(coder, "is debugging");
	sleep_ms(coder->simulation->config.time_to_debug);
}

static void	run_refactor(t_coder *coder)
{
	print_status(coder, "is refactoring");
	sleep_ms(coder->simulation->config.time_to_refactor);
}

static void	set_dongle_order(t_coder *coder,
		t_dongle **first, t_dongle **second)
{
	if (coder->left->id < coder->right->id)
	{
		*first = coder->left;
		*second = coder->right;
	}
	else
	{
		*first = coder->right;
		*second = coder->left;
	}
}

static void	run_cycles(t_coder *coder,
		t_dongle *first, t_dongle *second)
{
	int	required;

	required = coder->simulation->config.number_of_compiles_required;
	while (coder->compile_count < required)
	{
		lock_dongle(coder, first);
		lock_dongle(coder, second);
		run_compile(coder);
        unlock_dongle(coder, second);
        unlock_dongle(coder, first);
		if (coder->compile_count >= required)
			break ;
		run_debug(coder);
		run_refactor(coder);
	}
}

static void	run_single_coder(t_coder *coder)
{
	lock_dongle(coder, coder->left);
    print_status(coder, "has only one dongle and cannot compile");
	unlock_dongle(coder, coder->left);
}

void	*coder_routine(void *argument)
{
	t_coder		*coder;
	t_dongle	*first;
	t_dongle	*second;

	coder = (t_coder *)argument;
	if (!coder || !coder->simulation
		|| !coder->left || !coder->right)
		return (NULL);
	if (coder->left == coder->right)
	{
		run_single_coder(coder);
		return (NULL);
	}
    set_dongle_order(coder, &first, &second);
    run_cycles(coder, first, second);
	return (NULL);
}

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
