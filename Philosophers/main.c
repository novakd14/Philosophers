/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 09:10:52 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/20 00:17:24 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_status	check_options(int argc, char **argv, t_options *options)
{
	options->philo_num = ph_atoi(argv[1]);
	options->die_time = ph_atoi(argv[2]);
	options->eat_time = ph_atoi(argv[3]);
	options->sleep_time = ph_atoi(argv[4]);
	if (options->philo_num == -1 || options->die_time == -1
		|| options->eat_time == -1 || options->sleep_time == -1)
		return (FAILURE);
	options->must_eat = -1;
	if (argc == 6)
		options->must_eat = ph_atoi(argv[5]);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_options		options;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("Time of day (us): %li\n", tv.tv_usec);
	if ((argc != 5 && argc != 6) || check_options(argc, argv,
			&options) == FAILURE)
	{
		mess_wrong_input();
		return (FAILURE);
	}
	printf("This program will do some thinking and eating.\n");
	printf("Number of philosophers: %i\n", options.philo_num);
	printf("Time to die: %i\n", options.die_time);
	printf("Time to eat: %i\n", options.eat_time);
	printf("Time to sleep: %i\n", options.sleep_time);
	printf("Number of times each philo must eat: %i\n", options.must_eat);
	return (SUCCESS);
}
