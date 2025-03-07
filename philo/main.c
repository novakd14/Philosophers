/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 09:10:52 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/29 10:16:40 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_variables(t_prop *prop, t_table *table)
{
	memset(prop, 0, sizeof(t_prop));
	memset(table, 0, sizeof(t_table));
}

static t_status	check_properties(int argc, char **argv, t_prop *prop)
{
	prop->philo_count = ph_atoi(argv[1]);
	if (prop->philo_count < 1)
		return (FAILURE);
	prop->die_time = ph_atoi(argv[2]);
	if (prop->die_time < 1)
		return (FAILURE);
	prop->eat_time = ph_atoi(argv[3]);
	if (prop->eat_time < 1)
		return (FAILURE);
	prop->sleep_time = ph_atoi(argv[4]);
	if (prop->sleep_time < 1)
		return (FAILURE);
	prop->must_eat = -1;
	if (argc == 6)
	{
		prop->must_eat = ph_atoi(argv[5]);
		if (prop->must_eat < 1)
			return (FAILURE);
	}
	return (SUCCESS);
}

static t_status	check_input(int argc, char **argv, t_prop *prop)
{
	if (argc != 5 && argc != 6)
	{
		error_message("Wrong number of arguments.");
		print_corr_format();
		return (FAILURE);
	}
	if (check_properties(argc, argv, prop) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	print_properties(t_prop *prop)
{
	printf("--------------------------\n");
	printf("Number of philosophers: %i\n", prop->philo_count);
	printf("Time to die: %i\n", prop->die_time);
	printf("Time to eat: %i\n", prop->eat_time);
	printf("Time to sleep: %i\n", prop->sleep_time);
	if (prop->must_eat > 0)
		printf("Number of times each philo must eat: %i\n", prop->must_eat);
	printf("--------------------------\n");
}

int	main(int argc, char **argv)
{
	t_prop	prop;
	t_table	table;

	init_variables(&prop, &table);
	if (check_input(argc, argv, &prop) == FAILURE)
		return (FAILURE);
	print_properties(&prop);
	if (prepare_simulation(&prop, &table) == FAILURE)
		return (FAILURE);
	start_simulation(&prop, &table);
	return (SUCCESS);
}
