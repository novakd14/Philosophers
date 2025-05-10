/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 09:10:52 by dnovak            #+#    #+#             */
/*   Updated: 2025/05/10 19:51:54 by dnovak           ###   ########.fr       */
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
	prop->philo_count = ph_atoi(argv[1], TRUE);
	if (prop->philo_count < 1)
		return (FAILURE);
	prop->die_time = ph_atoi(argv[2], TRUE);
	if (prop->die_time < 1)
		return (FAILURE);
	prop->eat_time = ph_atoi(argv[3], TRUE);
	if (prop->eat_time < 1)
		return (FAILURE);
	prop->sleep_time = ph_atoi(argv[4], TRUE);
	if (prop->sleep_time < 1)
		return (FAILURE);
	prop->meals_num = -1;
	if (argc == 6)
	{
		prop->meals_num = ph_atoi(argv[5], TRUE);
		if (prop->meals_num < 1)
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
	if (prop->meals_num > 0)
		printf("Number of times each philo must eat: %i\n", prop->meals_num);
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
