/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:50:58 by dnovak            #+#    #+#             */
/*   Updated: 2025/05/12 15:44:55 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ph_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (*(str + len) != '\0')
		++len;
	return (len);
}

void	error_message(char *message)
{
	int	fd;

	fd = STDERR_FILENO;
	write(fd, "\033[1;31m", 8);
	write(fd, "ERROR: ", 8);
	write(fd, "\033[0m", 5);
	write(fd, message, ph_strlen(message));
	write(fd, "\n", 1);
}

void	print_corr_format(void)
{
	write(STDERR_FILENO,
		"Please enter arguments as positive integers in this format:\n"
		"\033[0;33m"
		"./philo number_of_philosophers time_to_die time_to_eat"
		" time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
		"\033[0m",
		185);
}

static void	set_color(t_action action)
{
	if (action == FORK)
		printf("\033[0;34m");
	else if (action == EAT)
		printf("\033[0;32m");
	else if (action == SLEEP)
		printf("\033[0;35m");
	else if (action == THINK)
		printf("\033[0;33m");
	else if (action == DIE)
		printf("\033[0;31m");
}

void	print_log(t_prop *prop, int philo_num, t_action action)
{
	pthread_mutex_lock(&(prop->log_mutex));
	if (prop->sim_state == RUN)
	{
		set_color(action);
		printf("%li ms [%i] ", curr_time_ms(prop), philo_num);
		if (action == FORK)
			printf("has taken a fork\n");
		else if (action == EAT)
			printf("is eating\n");
		else if (action == SLEEP)
			printf("is sleeping\n");
		else if (action == THINK)
			printf("is thinking\n");
		else if (action == DIE)
		{
			printf("died\n");
			prop->sim_state = END;
		}
		printf("\033[0m");
	}
	pthread_mutex_unlock(&(prop->log_mutex));
}
