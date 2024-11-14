/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:28:43 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/06 09:24:03 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_strlen(char *str)
{
	long	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

static int	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		str = "(null)";
	if (write(fd, str, ft_strlen(str)) == -1)
		return (-1);
	return (0);
}

static int	overflow_return(int sign)
{
	if (sign == 1)
		return (-1);
	else if (sign == -1)
		return (0);
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
	if ((*str == '+' || *str == '-') && (*(str + 1) != '\0'))
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

int	error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}
