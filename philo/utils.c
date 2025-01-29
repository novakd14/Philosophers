/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 02:01:49 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/29 09:29:57 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ph_max3(long a, long b, long c)
{
	if (a > b && a > c)
		return (a);
	else if (b > c)
		return (b);
	return (c);
}

long	curr_time_ms(t_prop *prop)
{
	struct timeval	tv;
	long			curr_time;

	gettimeofday(&tv, NULL);
	curr_time = (tv.tv_sec - prop->sim_start.tv_sec) * 1000;
	curr_time += (tv.tv_usec - prop->sim_start.tv_usec) / 1000;
	return (curr_time);
}
