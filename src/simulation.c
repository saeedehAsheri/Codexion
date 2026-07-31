#include "../includes/codexion.h"

static void	set_dongle_order(t_coder *coder,
		t_dongle **first, t_dongle **second)
{
	if (coder->left->id < coder->right->id)
	{
		*first = coder->left;
		*second = coder->right;
	}
	else
	{
		*first = coder->right;
		*second = coder->left;
	}
}

static void	run_cycles(t_coder *coder,
		t_dongle *first, t_dongle *second)
{
	int	required;

	required = coder->simulation->config.number_of_compiles_required;
	while (!simulation_is_finished(coder->simulation)
		&& get_compile_count(coder) < required)
	{
		if (!lock_dongle(coder, first))
			break ;
		if (!lock_dongle(coder, second))
		{
			unlock_dongle(coder, first);
			break ;
		}
		if (!run_compile(coder))
		{
			unlock_dongle(coder, second);
			unlock_dongle(coder, first);
			break ;
		}
		unlock_dongle(coder, second);
		unlock_dongle(coder, first);
		if (get_compile_count(coder) >= required)
			break ;
		if (!run_debug(coder) || !run_refactor(coder))
			break ;
	}
}

static void	run_single_coder(t_coder *coder)
{
	if (!lock_dongle(coder, coder->left))
		return ;
	while (!simulation_is_finished(coder->simulation))
		usleep(500);
	unlock_dongle(coder, coder->left);
}

void	*coder_routine(void *argument)
{
	t_coder		*coder;
	t_dongle	*first;
	t_dongle	*second;

	coder = (t_coder *)argument;
	if (!coder || !coder->simulation
		|| !coder->left || !coder->right)
		return (NULL);
	if (coder->left == coder->right)
	{
		run_single_coder(coder);
		return (NULL);
	}
	set_dongle_order(coder, &first, &second);
	run_cycles(coder, first, second);
	return (NULL);
}
