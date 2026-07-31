#include "../includes/codexion.h"

int	main(int argc, char **argv)
{
	t_config		config;
	t_simulation	init_values;

	/* check the number of args */
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
	/* Parse arguments */
	if (!get_arguments(&config, argv))
		return (1);
	/* printf("Arguments are valid.\n"); */
	/* initialize simulation */
	if (!init_simulation(&config, &init_values))
	{
		printf("Error: simulation initialization failed.\n");
		return (1);
	}
	if (!set_start_time(&init_values))
	{
		printf("Error: could not set start time.\n");
		free_simulation(&init_values);
		return (1);
	}
	set_coders_start_time(&init_values);
	printf("Simulation initialized successfully.\n");
	/*
	for (int i = 0;
		i < init_values.config.number_of_coders; i++)
	{
		printf("%d   ", init_values.coders[i].id);
		printf("%d   ", init_values.coders[i].left->id);
		printf("%d \n", init_values.coders[i].right->id);
	}
	*/
	/* start simulation */
	if (!create_threads(&init_values))
	{
		printf("Error: threads were not created.\n");
		free_simulation(&init_values);
		return (1);
	}
	if (!create_monitor_thread(&init_values))
	{
		printf("Error: monitor thread was not created.\n");
		finish_simulation(&init_values);
		join_threads(&init_values);
		free_simulation(&init_values);
		return (1);
	}
	/* wait for threads */
	if (!join_monitor_thread(&init_values))
	{
		printf("Error: could not join monitor thread.\n");
		finish_simulation(&init_values);
		join_threads(&init_values);
		free_simulation(&init_values);
		return (1);
	}
	if (!join_threads(&init_values))
	{
		printf("Error: could not join coder threads.\n");
		free_simulation(&init_values);
		return (1);
	}
	/* cleanup */
	free_simulation(&init_values);
	return (0);
}
