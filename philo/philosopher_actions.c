/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:59:44 by dnovak            #+#    #+#             */
/*   Updated: 2025/05/13 13:30:45 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_sleeping(t_philo_state *philo_state, t_times *actions_times,
		t_data *data)
{
	actions_times->last_action += data->prop->eat_time;
	pthread_mutex_lock(&(data->first_fork->mutex));
	data->first_fork->state = FREE;
	pthread_mutex_unlock(&(data->first_fork->mutex));
	data->taken_first_fork = FALSE;
	pthread_mutex_lock(&(data->second_fork->mutex));
	data->second_fork->state = FREE;
	pthread_mutex_unlock(&(data->second_fork->mutex));
	update_eaten_meals(data);
	*philo_state = SLEEPING;
	print_log(data->prop, data->philo_num, SLEEP);
}

static void	start_thinking(t_philo_state *philo_state, t_times *actions_times,
		t_data *data)
{
	actions_times->last_action += data->prop->sleep_time;
	*philo_state = THINKING;
	print_log(data->prop, data->philo_num, THINK);
}

static void	start_eating(t_philo_state *philo_state, t_times *actions_times,
		t_data *data)
{
	if (data->second_fork == NULL)
		return ;
	pthread_mutex_lock(&(data->first_fork->mutex));
	if (data->first_fork->state == FREE || data->taken_first_fork == TRUE)
	{
		take_first_fork(data);
		pthread_mutex_lock(&(data->second_fork->mutex));
		if (data->second_fork->state == FREE)
		{
			actions_times->last_action = ph_max3(data->first_fork->time_freed,
					data->second_fork->time_freed, actions_times->last_action);
			data->first_fork->time_freed = actions_times->last_action
				+ data->prop->eat_time;
			data->second_fork->time_freed = data->first_fork->time_freed;
			data->second_fork->state = TAKEN;
			print_log(data->prop, data->philo_num, FORK);
			actions_times->last_eating = actions_times->last_action;
			*philo_state = EATING;
			print_log(data->prop, data->philo_num, EAT);
		}
		pthread_mutex_unlock(&(data->second_fork->mutex));
	}
	pthread_mutex_unlock(&(data->first_fork->mutex));
}

void	take_action(t_philo_state *philo_state, t_times *actions_times,
		t_data *data)
{
	if (curr_time_ms(data->prop)
		- actions_times->last_eating > data->prop->die_time)
	{
		actions_times->last_action = curr_time_ms(data->prop);
		print_log(data->prop, data->philo_num, DIE);
	}
	else if (*philo_state == EATING && curr_time_ms(data->prop)
		- actions_times->last_action >= data->prop->eat_time)
		start_sleeping(philo_state, actions_times, data);
	else if (*philo_state == SLEEPING && curr_time_ms(data->prop)
		- actions_times->last_action >= data->prop->sleep_time)
	{
		start_thinking(philo_state, actions_times, data);
		start_eating(philo_state, actions_times, data);
	}
	else if (*philo_state == THINKING)
		start_eating(philo_state, actions_times, data);
}
