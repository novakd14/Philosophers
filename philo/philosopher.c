/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:45:25 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/27 02:00:38 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *data)
{
	int				philo_num;
	t_prop			*prop;
	t_times			actions_times;
	t_philo_state	philo_state;

	philo_num = ((t_data *)data)->philo_id + 1;
	prop = ((t_data *)data)->prop;
	philo_state = THINKING;
	while (prop->sim_state == PREP)
		usleep(SIM_STEP);
	actions_times.last_action = curr_time_ms(prop);
	actions_times.last_eating = actions_times.last_action;
	printf("%li ms %i is thinking\n", actions_times.last_action, philo_num);
	while (prop->sim_state == RUN)
	{
		take_action(&philo_state, &actions_times, data, philo_num);
		usleep(SIM_STEP);
	}
	free(data);
	return (NULL);
}
