#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <stdio.h>
# include <string.h>
#include <stdlib.h>
#include <sys/time.h>
/*lib for having different running path in the program using threads*/
# include <pthread.h>
# include <unistd.h>

typedef struct s_dongle	t_dongle;
typedef struct s_simulation t_simulation;

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
	t_dongle *left;
	t_dongle *right;
	t_simulation	*simulation;
	pthread_t	thread_id;
}	t_coder;

typedef struct s_dongle
{
	int		id;
	//int		is_available;
	long	available_at;
	pthread_mutex_t	dongle_mutex;
}	t_dongle;

typedef struct s_simulation
{
	t_config		config;
	t_coder			*coders;
	t_dongle		*dongles;
	long			start_time;
	int				is_finished;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	int				print_mutex_initialized;
	int				state_mutex_initialized;
}	t_simulation;

int	    get_arguments(t_config *config, char **argv);
int	    get_scheduler(const char *str, t_scheduler *scheduler);
int     parse_integer(const char *str, int *result, int allow_zero);
//void	set_config_fields(t_config *config, int **values);
//static int		parse_numeric_arguments(t_config *config, char **argv);
int 	init_simulation(t_config *config,t_simulation *init_values);
int		init_coders(t_simulation *init_values);
int		init_dongles(t_simulation *init_values);
void	free_simulation(t_simulation *init_values);
long	get_time_ms(void);
int		set_start_time(t_simulation *init_values);
int		create_threads(t_simulation *simulation);
int		join_threads(t_simulation *simulation);
void	*coder_routine(void *argument);
void	print_status(t_coder *coder, const char *message);
void	sleep_ms(long milliseconds);
void	lock_dongle(t_coder *coder, t_dongle *dongle);
void	unlock_dongle(t_coder *coder, t_dongle *dongle);
void	cleanup_dongles(t_simulation *simulation);
void	run_compile(t_coder *coder);
void	run_debug(t_coder *coder);
void	run_refactor(t_coder *coder);
void	update_compile_start(t_coder *coder);
void	increment_compile_count(t_coder *coder);
int		get_compile_count(t_coder *coder);

#endif