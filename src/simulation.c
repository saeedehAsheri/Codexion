#include "../includes/codexion.h"

void	*coder_routine(void *argument)
{
	t_coder	*coder;

	coder = (t_coder *)argument;
	printf("Coder %d started\n", coder->id);
	return (NULL);
}

int create_threads(t_simulation *init_values)
{
    int count;
    int i;

    if (!init_values|| !init_values->coders)
		return (0);

    count = init_values->config.number_of_coders;
    i = 0;
    while(i < count)
    {
    //Create thread and choose afunction to execute
    if(pthread_create(
        &init_values->coders[i].thread_id,
        NULL,
        coder_routine,
        &init_values->coders[i]
    ) != 0){
        printf("Error: thread creation failed.\n");
        return (0);
    }
    i++;
    }
    return (1);
}
int join_threads(t_simulation *init_values)
{
    int count;
    int i;

    if (!init_values|| !init_values->coders)
		return (0);

    count = init_values->config.number_of_coders;
    i = 0;
    while(i < count)
    {
        //ask main thread (main) Wait till new thread ends
        if(pthread_join(init_values->coders[i].thread_id, NULL) != 0)
            return (0);
        i++;
    }
    
    return (1);
}
