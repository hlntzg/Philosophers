/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:48:40 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/15 09:22:41 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * elapsed_time - Calculate the elapsed time since a given start time in ms.
 * @start: The starting time from time structure (t_time).
 * 
 * This function computes the difference between the end (current) time and
 * start time in miliseconds. It uses gettimeofday() to get current time.
 * 
 * Return: The elapsed time in ms, or -1 if gettimeofday() fails.
 */
long	elapsed_time(t_time start)
{
	t_time	end;

	if (gettimeofday(&end, NULL) == -1)
		return (-1);
	return ((end.tv_sec * 1000 + end.tv_usec / 1000)
		- (start.tv_sec * 1000 + start.tv_usec / 1000));
}

/**
 * ft_sleep - Custom sleep function for philosophers simulation.
 * @philo: Pointer to the philosopher structure.
 * @time: Time to suspend the thread in miliseconds.
 *
 * This function uses short sleep intervals (100 microseconds) to allow
 * frequent state checks (end of simulation) and monitors the elapsed time to
 * ensure accurate sleep duration (time). If the simulation is over during
 * sleep, it handles resource release if interrupted while eating.
 *
 * Return: On success ft_sleep() returns 0; -1 if interrupted or error occurs.
 */
int	ft_sleep(t_philo *philo, long time)
{
	t_time	s_start;

	if (gettimeofday(&s_start, NULL) == -1)
		return (-1);
	while (elapsed_time(s_start) < time)
	{
		usleep(100);
		if (get_state(philo) == OVER)
		{
			if (get_status(philo) == EATING)
				let_the_forks(philo);
			return (-1);
		}
	}
	return (0);
}
