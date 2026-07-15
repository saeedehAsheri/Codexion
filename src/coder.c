#include "../includes/codexion.h"



int	init_coders(t_simulation *init_values)
{
    int i;
    int count;

    i = 0;
    count = init_values->config.number_of_coders;
    init_values->coders = malloc(sizeof(t_coder) * count);
    if(!init_values->coders)
        return (0);

    while(i < count)
    {
        init_values->coders[i].id = i + 1;
        init_values->coders[i].compile_count = 0;
        init_values->coders[i].last_compile_start = 0;
        init_values->coders[i].left = &init_values->dongles[i];
        init_values->coders[i].right
	    = &init_values->dongles[(i + 1) % count];
        i++;
    }

    return(1);
}
