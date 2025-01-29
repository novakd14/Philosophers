/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:45:25 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/29 10:13:59 by dnovak           ###   ########.fr       */
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
	memset(&actions_times, 0, sizeof(t_times));
	while (prop->sim_state == PREP)
		usleep(SIM_STEP);
	philo_state = THINKING;
	print_log(prop, philo_num, THINK);
	while (prop->sim_state == RUN)
	{
		take_action(&philo_state, &actions_times, data, philo_num);
		usleep(SIM_STEP);
	}
	free(data);
	return (NULL);
}
