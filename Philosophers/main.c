/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 09:10:52 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/18 09:58:45 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 5 && argc != 6)
	{
		write(STDERR_FILENO, "ERROR: Wrong number of arguments.\n", 35);
		write(STDERR_FILENO,
			"./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
			114);
		return (1);
	}
	printf("This program will do some thinking (and eating).\n");
	return (0);
}
