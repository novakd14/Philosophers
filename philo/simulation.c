/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:54:06 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/23 23:06:01 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	curr_time_ms(t_data *data)
{
	struct timeval	tv;
	long			curr_time;

	gettimeofday(&tv, NULL);
	curr_time = (tv.tv_sec - data->prop->sim_start.tv_sec) * 1000;
	curr_time += (tv.tv_usec - data->prop->sim_start.tv_usec) / 1000;
	return (curr_time);
}

static void	*philosopher(void *data)
{
	int	philo_num;

	philo_num = ((t_data *)data)->philo_id + 1;
	printf("Start of simulation: %li\n", (curr_time_ms((t_data *)data)));
	printf("Hello, I am philosopher number %i.\n", philo_num);
	while (((t_data *)data)->prop->sim_end == FALSE)
	{
		printf("%li %i is eating\n", curr_time_ms((t_data *)data), philo_num);
		usleep(((t_data *)data)->prop->eat_time * 1000);
		printf("%li %i is sleeping\n", curr_time_ms((t_data *)data), philo_num);
		usleep(((t_data *)data)->prop->sleep_time * 1000);
		printf("%li %i is thinking\n", curr_time_ms((t_data *)data), philo_num);
	}
	free(data);
	return (NULL);
}

t_status	start_simulation(t_prop *prop)
{
	pthread_t	*philo;
	t_data		*data;
	int			id;

	gettimeofday(&(prop->sim_start), NULL);
	philo = (pthread_t *)malloc(sizeof(pthread_t) * prop->philo_num);
	if (philo == NULL)
	{
		error_message("Could not allocate memory.");
		return (FAILURE);
	}
	memset(philo, 0, sizeof(pthread_t) * prop->philo_num);
	id = 0;
	while (id < prop->philo_num)
	{
		data = (t_data *)malloc(sizeof(t_data));
		if (data == NULL)
		{
			error_message("Could not allocate memory.");
			return (FAILURE);
		}
		prop->sim_end = FALSE;
		data->philo_id = 0;
		data->prop = prop;
		if (pthread_create(&philo, NULL, &philosopher, data) != SUCCESS)
		{
			free(data);
			prop->sim_end = TRUE;
			error_message("Could not create thread.");
			return (FAILURE);
		}
	}
	sleep(3);
	prop->sim_end = TRUE;
	sleep(5);
	return (SUCCESS);
}
