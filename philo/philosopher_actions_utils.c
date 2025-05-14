/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:59:44 by dnovak            #+#    #+#             */
/*   Updated: 2025/05/14 15:18:19 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_first_fork(t_data *data)
{
	if (data->taken_first_fork == FALSE)
	{
		print_log(data->prop, data->philo_num, FORK);
		data->first_fork->state = TAKEN;
		data->taken_first_fork = TRUE;
	}
}

void	update_eaten_meals(t_data *data)
{
	pthread_mutex_lock(&(data->prop->log_mutex));
	data->meals_eaten += 1;
	if (data->meals_eaten == data->prop->meals_num)
	{
		data->prop->full_philo += 1;
		if (data->prop->meals_num != -1
			&& data->prop->full_philo == data->prop->philo_count)
			data->prop->sim_state = END;
	}
	pthread_mutex_unlock(&(data->prop->log_mutex));
}
