#include "../includes/codexion.h"

void	print_status(t_coder *coder, const char *message)
{
	long	timestamp;

    pthread_mutex_lock(&coder->simulation->print_mutex);
	timestamp = get_time_ms() - coder->simulation->start_time;
	printf("%ld %d %s\n", timestamp, coder->id, message);
    pthread_mutex_unlock(&coder->simulation->print_mutex);
}
