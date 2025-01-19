/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:50:58 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/19 23:58:21 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mess_wrong_input(void)
{
	write(STDERR_FILENO, "ERROR: Wrong input arguments.\n", 31);
	write(STDERR_FILENO, "Please enter arguments as non-negative integers", 48);
	write(STDERR_FILENO, " in this format:\n", 18);
	write(STDERR_FILENO, "./philo number_of_philosophers time_to_die", 43);
	write(STDERR_FILENO, " time_to_eat time_to_sleep", 27);
	write(STDERR_FILENO, " [number_of_times_each_philosopher_must_eat]\n", 46);
}
