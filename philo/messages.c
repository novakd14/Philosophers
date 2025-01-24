/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:50:58 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/23 10:34:10 by dnovak           ###   ########.fr       */
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
