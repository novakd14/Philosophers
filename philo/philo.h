/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 09:17:56 by dnovak            #+#    #+#             */
/*   Updated: 2025/05/10 19:53:21 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>  // pthread_create, pthread_join, pthread_detach,
						// pthread_mutex
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <string.h>   // memset
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // write, usleep

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# ifndef MAX_INT
#  define MAX_INT 2147483647
# endif

# ifndef SIM_STEP
#  define SIM_STEP 100
# endif

typedef enum e_status
{
	SUCCESS = 0,
	FAILURE = 1,
}					t_status;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1,
}					t_bool;

typedef enum e_sim_state
{
	PREP,
	RUN,
	END,
}					t_sim_state;

typedef enum e_philo_state
{
	THINKING,
	EATING,
	SLEEPING,
}					t_philo_state;

typedef enum e_fork_state
{
	FREE,
	TAKEN,
}					t_fork_state;

typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}					t_action;

typedef struct s_prop
{
	int				philo_count;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				meals_num;
	struct timeval	sim_start;
	t_sim_state		sim_state;
	pthread_mutex_t	log_mutex;
}					t_prop;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	t_fork_state	state;
	long			time_freed;
}					t_fork;

typedef struct s_table
{
	t_fork			*forks;
	pthread_t		*philo;
}					t_table;

typedef struct s_data
{
	int				philo_id;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_prop			*prop;
}					t_data;

typedef struct s_times
{
	long			curr_time;
	long			last_action;
	long			last_eating;
}					t_times;

t_status			prepare_simulation(t_prop *prop, t_table *table);
void				start_simulation(t_prop *prop, t_table *table);
void				*philosopher(void *data);
void				take_action(t_philo_state *philo_state,
						t_times *actions_times, t_data *data, int philo_num);

// Messages
void				error_message(char *message);
void				print_corr_format(void);
void				print_log(t_prop *prop, int philo_num, t_action action);

// Utils and cleaning functions
int					ph_atoi(const char *nptr, t_bool positive);
long				ph_max3(long a, long b, long c);
long				curr_time_ms(t_prop *prop);
void				free_forks(t_fork *forks, int count);
void				clean_philosophers(pthread_t *philo, int count,
						t_prop *prop, t_bool __end_sim);

#endif // PHILO_H
