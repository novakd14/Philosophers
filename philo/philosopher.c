/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:45:25 by dnovak            #+#    #+#             */
/*   Updated: 2025/05/14 16:40:18 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_for_start(t_data *data)
{
	pthread_mutex_lock(&(data->prop->log_mutex));
	pthread_mutex_unlock(&(data->prop->log_mutex));
}

static void	first_action(t_data *data, t_philo_state *philo_state)
{
	if (((t_data *)data)->philo_num % 2 == 0)
	{
		*philo_state = THINKING;
		print_log(data->prop, ((t_data *)data)->philo_num, THINK);
	}
	else if (((t_data *)data)->philo_num == data->prop->philo_count)
	{
		*philo_state = THINKING;
		print_log(data->prop, ((t_data *)data)->philo_num, THINK);
	}
	else
	{
		*philo_state = SLEEPING;
		print_log(data->prop, ((t_data *)data)->philo_num, SLEEP);
	}
}

static t_sim_state	check_sim_state(t_data *data)
{
	t_sim_state	sim_state;

	pthread_mutex_lock(&(data->prop->log_mutex));
	sim_state = data->prop->sim_state;
	pthread_mutex_unlock(&(data->prop->log_mutex));
	return (sim_state);
}

void	*philosopher(void *data)
{
	t_times			actions_times;
	t_philo_state	philo_state;

	memset(&actions_times, 0, sizeof(t_times));
	wait_for_start(data);
	first_action(data, &philo_state);
	while (check_sim_state(data) == RUN)
	{
		take_action(&philo_state, &actions_times, data);
		usleep(SIM_STEP);
	}
	free(data);
	return (NULL);
}
