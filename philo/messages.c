/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:50:58 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/29 10:43:24 by dnovak           ###   ########.fr       */
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

void	print_log(t_prop *prop, int philo_num, t_action action)
{
	pthread_mutex_lock(&(prop->log_mutex));
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
		printf("died\n");
	pthread_mutex_unlock(&(prop->log_mutex));
}
