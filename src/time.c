#include "../includes/codexion.h"

long    get_time_ms(void)
{
    struct  timeval time;
    //to save current time in the time variable
    if(gettimeofday(&time, NULL) != 0)
        return (-1);
    //tv_sec: number of seconds
    //tv_usec: Smaller part of 1 second in micro second
    return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}
int	set_start_time(t_simulation *init_values)
{
	long	start;
	int		i;

	if (!init_values || !init_values->coders)
		return (0);
	start = get_time_ms();
	if (start == -1)
		return (0);
	init_values->start_time = start;
	i = 0;
	while (i < init_values->config.number_of_coders)
	{
		init_values->coders[i].last_compile_start = start;
		i++;
	}
	return (1);
}

void	sleep_ms(long milliseconds)
{
	usleep((unsigned int)milliseconds * 1000);
}

int	set_simulation_start(t_simulation *simulation)
{
	int	i;

	simulation->start_time = get_time_ms();
	if (simulation->start_time < 0)
		return (0);
	i = 0;
	while (i < simulation->config.number_of_coders)
	{
		simulation->coders[i].last_compile_start
			= simulation->start_time;
		i++;
	}
	return (1);
}

int	interruptible_sleep(t_simulation *simulation, long duration)
{
	long	end_time;

	end_time = get_time_ms() + duration;
	while (get_time_ms() < end_time)
	{
		if (simulation_is_finished(simulation))
			return (0);
		usleep(500);
	}
	return (1);
}
