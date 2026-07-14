#include "../includes/codexion.h"

static void	set_config_fields(t_config *config, int **values)
{
	values[0] = &config->number_of_coders;
	values[1] = &config->time_to_burnout;
	values[2] = &config->time_to_compile;
	values[3] = &config->time_to_debug;
	values[4] = &config->time_to_refactor;
	values[5] = &config->number_of_compiles_required;
	values[6] = &config->dongle_cooldown;
}

static int	parse_numeric_arguments(t_config *config, char **argv)
{
	int	*values[7];
	int	allow_zero;
	int	i;

	set_config_fields(config, values);
	i = 0;
	while (i < 7)
	{
		allow_zero = (i != 0 && i != 5);
		if (!parse_integer(argv[i + 1], values[i], allow_zero))
			return (0);
		i++;
	}
	return (1);
}

int	get_arguments(t_config *config, char **argv)
{
	if (!config || !argv)
		return (0);
	if (!parse_numeric_arguments(config, argv))
		return (printf("Error: invalid numeric argument.\n"), 0);
	if (!get_scheduler(argv[8], &config->scheduler))
		return (printf("Error: scheduler must be fifo or edf.\n"), 0);
	return (1);
}
