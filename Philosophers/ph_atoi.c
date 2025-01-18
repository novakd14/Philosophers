/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:25:59 by dnovak            #+#    #+#             */
/*   Updated: 2025/01/18 10:07:33 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

// The ph_atoi() function converts the full string pointed to by nptr
// to non-negative int. The string has to begin with digit or '+' sign.
// RETURN VALUE: The converted value or -1 on error.
// NOTES: If ntpr == NULL return Segmentation fault
int	ph_atoi(const char *nptr)
{
	size_t	i;
	int		num;

	i = 0;
	if (*nptr == '+')
		i = 1;
	num = 0;
	while (*(nptr + i) != '\0')
	{
		if (ph_isdigit(*(nptr + i)) == 0)
			return (-1);
		num = num * 10 + *(nptr + i++) - '0';
	}
	return (num);
}
