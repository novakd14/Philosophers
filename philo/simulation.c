/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:42:07 by dnovak            #+#    #+#             */
/*   Updated: 2025/05/12 13:52:08 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_prop *prop, t_table *table)
{
	prop->sim_state = RUN;
	gettimeofday(&(prop->sim_start), NULL);
	pthread_mutex_unlock(&(prop->log_mutex));
	clean_philosophers(table->philo, prop->philo_count, prop, FALSE);
	free_forks(table->forks, prop->philo_count);
	pthread_mutex_destroy(&(prop->log_mutex));
}
