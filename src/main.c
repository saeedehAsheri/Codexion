#include "../includes/codexion.h"

int	main(int argc, char **argv)
{
	t_config	config;

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
	if (!get_arguments(&config, argv))
		return (1);
	printf("Arguments are valid.\n");
	/* initialize simulation */
	/* start simulation */
	/* wait for threads */
	/* cleanup */
	return (0);
}