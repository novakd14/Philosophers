/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:54:06 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/25 07:18:41 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	curr_time_ms(t_data *data)
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
	int		philo_num;
	t_prop	*prop;

	philo_num = ((t_data *)data)->philo_id + 1;
	prop = ((t_data *)data)->prop;
	printf("Philosopher number %i is ready for an action!\n", philo_num);
	while (prop->sim_status == PREP)
		usleep(500);
	while (prop->sim_status == RUN)
	{
		printf("Philosopher number %i is running.\n", philo_num);
		usleep(500000);
	}
	// printf("Start of simulation: %li\n", (curr_time_ms((t_data *)data)));
	// printf("Hello, I am philosopher number %i.\n", philo_num);
	// while (((t_data *)data)->prop->sim_status == RUN)
	// {
	// 	printf("%li %i is eating\n", curr_time_ms((t_data *)data),
	// philo_num);
	// 	usleep(((t_data *)data)->prop->eat_time * 1000);
	// 	printf("%li %i is sleeping\n", curr_time_ms((t_data *)data),
	// philo_num);
	// 	usleep(((t_data *)data)->prop->sleep_time * 1000);
	// 	printf("%li %i is thinking\n", curr_time_ms((t_data *)data),
	// philo_num);
	// }
	free(data);
	return (NULL);
}

void	free_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
		pthread_mutex_destroy(&(forks[i++]));
	free(forks);
}

t_status	prepare_forks(t_prop *prop, t_table *table)
{
	int	id;

	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* prop->philo_count);
	if (table->forks == NULL)
	{
		error_message("Could not allocate memory.");
		return (FAILURE);
	}
	id = 0;
	while (id < prop->philo_count)
	{
		if (pthread_mutex_init(&(table->forks[id]), NULL) != 0)
		{
			error_message("Could not initialize a mutex object.");
			free_forks(table->forks, id);
			return (FAILURE);
		}
		id++;
	}
	return (SUCCESS);
}

void	init_data(t_data *data, int id, t_prop *prop, pthread_mutex_t *forks)
{
	data->philo_id = id;
	data->prop = prop;
	if (prop->philo_count == 1)
	{
		data->first_fork = &(forks[id]);
		data->second_fork = NULL;
	}
	else
	{
		if (id % 2 == 0)
		{
			data->first_fork = &(forks[id]);
			data->second_fork = &(forks[(id + 1) % prop->philo_count]);
		}
		else
		{
			data->first_fork = &(forks[(id + 1) % prop->philo_count]);
			data->second_fork = &(forks[id]);
		}
	}
}

t_status	prepare_philo(t_prop *prop, t_table *table, int id)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
	{
		error_message("Could not allocate memory.");
		return (FAILURE);
	}
	init_data(data, id, prop, table->forks);
	if (pthread_create(&(table->philo[id]), NULL, &philosopher, data) != 0)
	{
		error_message("Could not create thread.");
		free(data);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	clean_philosophers(pthread_t *philo, int count, t_prop *prop)
{
	int	i;

	prop->sim_status = END;
	i = 0;
	while (i < count)
	{
		pthread_join(philo[i], NULL);
		++i;
	}
	free(philo);
}

t_status	prepare_philosophers(t_prop *prop, t_table *table)
{
	int	id;

	table->philo = (pthread_t *)malloc(sizeof(pthread_t) * prop->philo_count);
	if (table->philo == NULL)
		return (FAILURE);
	id = 0;
	while (id < prop->philo_count)
	{
		if (prepare_philo(prop, table, id) == FAILURE)
		{
			clean_philosophers(table->philo, id, prop);
			return (FAILURE);
		}
		id++;
	}
	return (SUCCESS);
}

t_status	prepare_simulation(t_prop *prop, t_table *table)
{
	if (prepare_forks(prop, table) == FAILURE)
		return (FAILURE);
	if (prepare_philosophers(prop, table) == FAILURE)
	{
		free_forks(table->forks, prop->philo_count);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	start_simulation(t_prop *prop, t_table *table)
{
	gettimeofday(&(prop->sim_start), NULL);
	prop->sim_status = RUN;
	sleep(3);
	clean_philosophers(table->philo, prop->philo_count, prop);
	free_forks(table->forks, prop->philo_count);
}
