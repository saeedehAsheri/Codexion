#include "../includes/codexion.h"


void destroy_all_mutexes(t_dongle *dongles, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        pthread_mutex_destroy(&dongles[i].dongle_mutex);
        i++;
    }
}
int	init_dongles(t_simulation *init_values)
{
    int i;

    i = 0;
    int count = init_values->config.number_of_coders;
    init_values->dongles = malloc(sizeof(t_dongle) * count);
    if(!init_values->dongles)
        return (0);

    while(i < count)
    {
        init_values->dongles[i].id = i + 1;
        //init_values->dongles[i].is_available = 1;
        init_values->dongles[i].available_at = 0;
        if(pthread_mutex_init(&init_values->dongles[i].dongle_mutex, NULL) != 0)
        {
            destroy_all_mutexes(init_values->dongles, i);
            free(init_values->dongles);
            init_values->dongles = NULL;
            return(0);
        }
        i++;
    }

    return(1);
}

void	lock_dongle(t_coder *coder, t_dongle *dongle)
{
	long	current_time;
	long	wait_time;

	while (1)
	{
		pthread_mutex_lock(&dongle->dongle_mutex);
		current_time = get_time_ms();
		if (current_time >= dongle->available_at)
		{
			print_status(coder, "has taken a dongle");
			return ;
		}
		wait_time = dongle->available_at - current_time;
		pthread_mutex_unlock(&dongle->dongle_mutex);
		if (wait_time > 0)
			sleep_ms(wait_time);
	}
}

void	unlock_dongle(t_coder *coder, t_dongle *dongle)
{
	dongle->available_at = get_time_ms()
		+ coder->simulation->config.dongle_cooldown;
	//dongle->is_available = 0;
	pthread_mutex_unlock(&dongle->dongle_mutex);
}
