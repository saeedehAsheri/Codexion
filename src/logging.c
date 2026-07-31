#include "../includes/codexion.h"

void	print_status(t_coder *coder, const char *message)
{
	t_simulation	*simulation;
	long			timestamp;

	simulation = coder->simulation;
	pthread_mutex_lock(&simulation->print_mutex);
	pthread_mutex_lock(&simulation->state_mutex);
	if (simulation->is_finished)
	{
		pthread_mutex_unlock(&simulation->state_mutex);
		pthread_mutex_unlock(&simulation->print_mutex);
		return ;
	}
	timestamp = get_time_ms() - simulation->start_time;
	printf("%ld %d %s\n", timestamp, coder->id, message);
	pthread_mutex_unlock(&simulation->state_mutex);
	pthread_mutex_unlock(&simulation->print_mutex);
}

void	print_burnout(t_coder *coder)
{
	t_simulation	*simulation;
	long			timestamp;

	simulation = coder->simulation;
	pthread_mutex_lock(&simulation->print_mutex);
	pthread_mutex_lock(&simulation->state_mutex);
	if (simulation->is_finished)
	{
		pthread_mutex_unlock(&simulation->state_mutex);
		pthread_mutex_unlock(&simulation->print_mutex);
		return ;
	}
	simulation->is_finished = 1;
	timestamp = get_time_ms() - simulation->start_time;
	printf("%ld %d burned out\n", timestamp, coder->id);
	pthread_mutex_unlock(&simulation->state_mutex);
	pthread_mutex_unlock(&simulation->print_mutex);
}
