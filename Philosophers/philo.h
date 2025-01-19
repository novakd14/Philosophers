/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 09:17:56 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/20 00:13:05 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>    // printf
#include <sys/time.h> // gettimeofday
#include <unistd.h>   // write

typedef struct s_options
{
	int	philo_num;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	must_eat;
}		t_options;

typedef enum e_status
{
	SUCCESS = 0,
	FAILURE = 1,
}		t_status;

int		ph_atoi(const char *nptr);

// Messages
void	mess_wrong_input(void);
