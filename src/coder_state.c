#include "../includes/codexion.h"

void	update_compile_start(t_coder *coder)
{
	pthread_mutex_lock(&coder->simulation->state_mutex);
	coder->last_compile_start = get_time_ms();
	pthread_mutex_unlock(&coder->simulation->state_mutex);
}

void	increment_compile_count(t_coder *coder)
{
	pthread_mutex_lock(&coder->simulation->state_mutex);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->simulation->state_mutex);
}

int	get_compile_count(t_coder *coder)
{
	int	count;

	pthread_mutex_lock(&coder->simulation->state_mutex);
	count = coder->compile_count;
	pthread_mutex_unlock(&coder->simulation->state_mutex);
	return (count);
}
