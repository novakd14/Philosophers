/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:38:28 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/27 02:29:52 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_fork *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
		pthread_mutex_destroy(&(forks[i++].mutex));
	free(forks);
}

void	clean_philosophers(pthread_t *philo, int count, t_prop *prop,
		t_bool __end_sim)
{
	int	i;

	if (__end_sim == TRUE)
		prop->sim_state = END;
	i = 0;
	while (i < count)
	{
		pthread_join(philo[i], NULL);
		++i;
	}
	free(philo);
}
