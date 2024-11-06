/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:48:40 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/06 08:54:13 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	elapsed_time(t_time start)
{
	t_time	end;
	long	elapsed_ms;

	if (gettimeofday(&end, NULL) == -1)
		return (-1);
	elapsed_ms = (end.tv_sec - start.tv_sec) * 1000
		+ (end.tv_usec - start.tv_usec) / 1000;
	return (elapsed_ms);
}

int	ft_usleep(t_philo *philo, long time)
{
	t_time	s_start;
	long	current;

	(void)philo;
	if (gettimeofday(&s_start, NULL) == -1)
		return (-1);
	while (1)
	{
		if (get_state(philo) == OVER)
		{
			if (get_status(philo) == EATING)
				let_the_forks(philo);
			return (-1);
		}
		current = elapsed_time(s_start);
		if (current == -1)
			return (-1);
		if (current >= time)
			break ;
		usleep(100);
	}
	return (0);
}
