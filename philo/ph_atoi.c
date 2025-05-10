/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovak <dnovak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:25:59 by dnovak            #+#    #+#             */
/*   Updated: 2025/05/10 19:50:35 by dnovak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

// The ph_atoi() function converts the full string pointed to by nptr
// to positive int. The string has to contain only digits.
// RETURN VALUE: The converted value or -1 on error.
// NOTES: If ntpr == NULL return Segmentation fault
int	ph_atoi(const char *nptr, t_bool positive)
{
	size_t	i;
	int		num;
	int		next_digit;

	i = 0;
	num = 0;
	while (*(nptr + i) != '\0')
	{
		if (ph_isdigit(*(nptr + i)) == FALSE)
		{
			error_message("Arguments have to contain only digits.");
			return (-1);
		}
		next_digit = *(nptr + i++) - '0';
		if (num > MAX_INT / 10 || num * 10 > MAX_INT - next_digit)
		{
			error_message("Integer overflow.");
			return (-1);
		}
		num = num * 10 + next_digit;
	}
	if (num == 0 && positive == TRUE)
		error_message("Arguments have to be positive integers.");
	return (num);
}
