#include "../includes/codexion.h"

int	run_compile(t_coder *coder)
{
	update_compile_start(coder);
	print_status(coder, "is compiling");
	if (!interruptible_sleep(coder->simulation,
			coder->simulation->config.time_to_compile))
		return (0);
	increment_compile_count(coder);
	return (1);
}

int	run_debug(t_coder *coder)
{
	print_status(coder, "is debugging");
	return (interruptible_sleep(coder->simulation,
			coder->simulation->config.time_to_debug));
}

int	run_refactor(t_coder *coder)
{
	print_status(coder, "is refactoring");
	return (interruptible_sleep(coder->simulation,
			coder->simulation->config.time_to_refactor));
}
