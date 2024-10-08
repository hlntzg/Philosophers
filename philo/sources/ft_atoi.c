/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:39:34 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/08 15:49:38 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	overflow_return(int sign)
{
	if (sign == 1)
		return (-1);
	else if (sign == -1)
		return (0);
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;
	int	tmp;

	result = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if ((*str == '+' || *str '-') && (*(str + 1) != '\0'))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		tmp = result * 10 + (*str - '0');
		if (tmp / 10 != result)
			return (overflow_return(sign));
		result = tmp;
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (sign * result);
}
