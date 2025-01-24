/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 09:17:56 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/24 09:36:48 by dnovak           ###   ########.fr       */
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

typedef struct s_prop
{
	int				philo_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	struct timeval	sim_start;
	t_bool			sim_end;
}					t_prop;

typedef struct s_data
{
	int				philo_id;
	t_prop			*prop;
}					t_data;

t_status			start_simulation(t_prop *prop);

// Messages
void				error_message(char *message);
void				print_corr_format(void);

// Utils
int					ph_atoi(const char *nptr);

#endif // PHILO_H
