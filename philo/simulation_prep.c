/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_prep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:54:06 by dnovak            #+#    #+#             */
/*   Updated: 2025/05/14 21:09:22 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	prepare_forks(t_prop *prop, t_table *table)
{
	int	id;

	table->forks = (t_fork *)calloc(prop->philo_count, sizeof(t_fork));
	if (table->forks == NULL)
	{
		error_message("Could not allocate memory.");
		return (FAILURE);
	}
	id = 0;
	while (id < prop->philo_count)
	{
		if (pthread_mutex_init(&(table->forks[id].mutex), NULL) != 0)
		{
			error_message("Could not initialize a mutex object.");
			free_forks(table->forks, id);
			return (FAILURE);
		}
		table->forks[id].state = FREE;
		++id;
	}
	return (SUCCESS);
}

static void	init_data(t_data *data, int id, t_prop *prop, t_fork *forks)
{
	data->philo_num = id + 1;
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

static t_status	prepare_philo(t_prop *prop, t_table *table, int id)
{
	t_data	*data;

	data = (t_data *)calloc(1, sizeof(t_data));
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

static t_status	prepare_philosophers(t_prop *prop, t_table *table)
{
	int	id;

	table->philo = (pthread_t *)calloc(prop->philo_count, sizeof(pthread_t));
	if (table->philo == NULL)
	{
		error_message("Could not allocate memory.");
		return (FAILURE);
	}
	id = 0;
	while (id < prop->philo_count)
	{
		if (prepare_philo(prop, table, id) == FAILURE)
		{
			clean_philosophers(table->philo, id, prop, TRUE);
			return (FAILURE);
		}
		++id;
	}
	return (SUCCESS);
}

t_status	prepare_simulation(t_prop *prop, t_table *table)
{
	prop->sim_state = PREP;
	if (pthread_mutex_init(&(prop->log_mutex), NULL) != 0)
	{
		error_message("Could not initialize a mutex object.");
		return (FAILURE);
	}
	if (prepare_forks(prop, table) == FAILURE)
	{
		pthread_mutex_destroy(&(prop->log_mutex));
		return (FAILURE);
	}
	pthread_mutex_lock(&(prop->log_mutex));
	if (prepare_philosophers(prop, table) == FAILURE)
	{
		free_forks(table->forks, prop->philo_count);
		pthread_mutex_unlock(&(prop->log_mutex));
		pthread_mutex_destroy(&(prop->log_mutex));
		return (FAILURE);
	}
	return (SUCCESS);
}
