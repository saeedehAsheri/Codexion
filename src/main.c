#include "../includes/codexion.h"

int	main(int argc, char **argv)
{
	t_config	config;
	t_simulation init_values;
	/*check the number of args */
	if (argc != 9)
	{
		printf(
			"Error: the number of arguments must be 8.\n"
			"Usage:\n"
			"./codexion <num_coders> <time_to_burnout> "
			"<time_to_compile> <time_to_debug> "
			"<time_to_refactor> <num_compiles> "
			"<cooldown_time> <fifo|edf>\n"
		);
		return (1);
	}
	/*Parse arguments*/
	if (!get_arguments(&config, argv))
		return (1);

	//printf("Arguments are valid.\n");
	/* initialize simulation */
	if(!init_simulation(&config, &init_values))
	{
		printf("Error: simulation initialization failed.\n");
		return(1);
	}
	printf("Simulation initialized successfully.\n");

	for(int i = 0; i < init_values.config.number_of_coders; i++)
	{
		printf("%d   ", init_values.coders[i].id);
		printf("%d   ", init_values.coders[i].left->id);
		printf("%d \n", init_values.coders[i].right->id);
	}
		
	free_simulation(&init_values);

	/* start simulation */
	/* wait for threads */
	/* cleanup */
	return (0);
}