/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:59:44 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/27 02:33:48 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_sleeping(t_philo_state *philo_state, t_times *actions_times,
		t_data *data, int philo_num)
{
	pthread_mutex_lock(&(data->first_fork->mutex));
	data->first_fork->state = FREE;
	pthread_mutex_unlock(&(data->first_fork->mutex));
	pthread_mutex_lock(&(data->second_fork->mutex));
	data->second_fork->state = FREE;
	pthread_mutex_unlock(&(data->second_fork->mutex));
	*philo_state = SLEEPING;
	actions_times->last_action = curr_time_ms(data->prop);
	printf("%li ms %i is sleeping\n", actions_times->last_action, philo_num);
}

static void	start_thinking(t_philo_state *philo_state, t_times *actions_times,
		t_data *data, int philo_num)
{
	*philo_state = THINKING;
	actions_times->last_action = curr_time_ms(data->prop);
	printf("%li ms %i is thinking\n", actions_times->last_action, philo_num);
}

static void	start_eating(t_philo_state *philo_state, t_times *actions_times,
		t_data *data, int philo_num)
{
	if (data->second_fork == NULL)
		return ;
	pthread_mutex_lock(&(data->first_fork->mutex));
	if (data->first_fork->state == FREE)
	{
		pthread_mutex_lock(&(data->second_fork->mutex));
		if (data->second_fork->state == FREE)
		{
			data->first_fork->state = TAKEN;
			actions_times->last_action = curr_time_ms(data->prop);
			printf("%li ms %i has taken a fork\n", actions_times->last_action,
				philo_num);
			data->second_fork->state = TAKEN;
			actions_times->last_action = curr_time_ms(data->prop);
			printf("%li ms %i has taken a fork\n", actions_times->last_action,
				philo_num);
			*philo_state = EATING;
			actions_times->last_action = curr_time_ms(data->prop);
			actions_times->last_eating = actions_times->last_action;
			printf("%li ms %i is eating\n", actions_times->last_action,
				philo_num);
		}
		pthread_mutex_unlock(&(data->second_fork->mutex));
	}
	pthread_mutex_unlock(&(data->first_fork->mutex));
}

void	take_action(t_philo_state *philo_state, t_times *actions_times,
		t_data *data, int philo_num)
{
	if (curr_time_ms(data->prop)
		- actions_times->last_eating >= data->prop->die_time + 1)
	{
		data->prop->sim_state = END;
		actions_times->last_action = curr_time_ms(data->prop);
		printf("%li ms %i died\n", actions_times->last_action, philo_num);
	}
	else if (*philo_state == EATING && curr_time_ms(data->prop)
		- actions_times->last_action >= data->prop->eat_time)
		start_sleeping(philo_state, actions_times, data, philo_num);
	else if (*philo_state == SLEEPING && curr_time_ms(data->prop)
		- actions_times->last_action >= data->prop->sleep_time)
	{
		start_thinking(philo_state, actions_times, data, philo_num);
		start_eating(philo_state, actions_times, data, philo_num);
	}
	else if (*philo_state == THINKING)
		start_eating(philo_state, actions_times, data, philo_num);
}
