/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:42:07 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/29 10:17:41 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_prop *prop, t_table *table)
{
	gettimeofday(&(prop->sim_start), NULL);
	prop->sim_state = RUN;
	clean_philosophers(table->philo, prop->philo_count, prop, FALSE);
	free_forks(table->forks, prop->philo_count);
	pthread_mutex_destroy(&(prop->log_mutex));
}
