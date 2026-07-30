#include "../includes/codexion.h"

void	run_compile(t_coder *coder)
{
	update_compile_start(coder);
	print_status(coder, "is compiling");
	sleep_ms(coder->simulation->config.time_to_compile);
	increment_compile_count(coder);
}

void	run_debug(t_coder *coder)
{
	print_status(coder, "is debugging");
	sleep_ms(coder->simulation->config.time_to_debug);
}

void	run_refactor(t_coder *coder)
{
	print_status(coder, "is refactoring");
	sleep_ms(coder->simulation->config.time_to_refactor);
}
