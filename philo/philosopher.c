/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:45:25 by dnovak            #+#    #+#             */
/*   Updated: 2025/05/13 13:54:59 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_sim_state	check_sim_state(t_prop *prop)
{
	t_sim_state	sim_state;

	pthread_mutex_lock(&(prop->log_mutex));
	sim_state = prop->sim_state;
	pthread_mutex_unlock(&(prop->log_mutex));
	return (sim_state);
}

static __useconds_t	sim_step(t_times *actions_times, t_prop *prop)
{
	double			temp;
	__useconds_t	result;

	temp = curr_time_ms(prop) - actions_times->last_eating;
	temp = temp / prop->die_time;
	result = MAX_SIM_STEP - (MAX_SIM_STEP - MIN_SIM_STEP) * temp;
	if (result < MIN_SIM_STEP)
		return (MIN_SIM_STEP);
	return (result);
}

void	*philosopher(void *data)
{
	t_prop			*prop;
	t_times			actions_times;
	t_philo_state	philo_state;

	prop = ((t_data *)data)->prop;
	memset(&actions_times, 0, sizeof(t_times));
	philo_state = THINKING;
	pthread_mutex_lock(&(prop->log_mutex));
	pthread_mutex_unlock(&(prop->log_mutex));
	print_log(prop, ((t_data *)data)->philo_num, THINK);
	if (((t_data *)data)->philo_num % 2 == 0)
		usleep(ph_min(prop->die_time, prop->eat_time) / 4 * 1000);
	while (check_sim_state(prop) == RUN)
	{
		take_action(&philo_state, &actions_times, data);
		usleep(sim_step(&actions_times, prop));
	}
	free(data);
	return (NULL);
}
