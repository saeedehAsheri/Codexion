#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <stdio.h>
# include <string.h>

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef struct s_config
{
	int			number_of_coders;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
	int			number_of_compiles_required;
	int			dongle_cooldown;
	t_scheduler	scheduler;
}	t_config;

typedef struct s_coder
{
	int		id;
	int		compile_count;
	long	last_compile_start;
}	t_coder;

typedef struct s_dongle
{
	int		id;
	int		is_available;
	long	available_at;
}	t_dongle;

typedef struct s_simulation
{
	t_config	config;
	t_coder		*coders;
	t_dongle	*dongles;
	long		start_time;
	int			is_finished;
}	t_simulation;

int	    get_arguments(t_config *config, char **argv);
int	    get_scheduler(const char *str, t_scheduler *scheduler);
int     parse_integer(const char *str, int *result, int allow_zero);
void	set_config_fields(t_config *config, int **values);
int		parse_numeric_arguments(t_config *config, char **argv);

#endif