/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 08:23:47 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/05 15:51:05 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	set_status(t_philo *philo, t_status status)
{
	pthread_mutex_lock(philo->philo_mtx);
	philo->status = status;
	if (status == EATING)
	{
		if (gettimeofday(&(philo->last_meal), NULL) == -1)
		{
			pthread_mutex_unlock(philo->philo_mtx);
			return (-1);
		}
	}
	pthread_mutex_unlock(philo->philo_mtx);
	return (0);
}

int	get_status(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->philo_mtx);
	status = philo->status;
	pthread_mutex_unlock(philo->philo_mtx);
	return (status);
}

void	get_message(t_philo *philo, char *str)
{
	long	timestamp;

	pthread_mutex_lock(philo->print);
	timestamp = elapsed_time(philo->arg.start);
	if (timestamp == -1)
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	if (str)
		printf("%ld %d %s\n", timestamp, philo->id, str);
	else
	{
		if (philo->status == THINKING)
			str = "is thinking";
		else if (philo->status == SLEEPING)
			str = "is sleeping";
		else if (philo->status == EATING)
			str = "is eating";
		printf("%ld %d %s\n", timestamp, philo->id, str);
	}
	pthread_mutex_unlock(philo->print);
}

void	set_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(philo->philo_mtx);
	philo->state = state;
	pthread_mutex_unlock(philo->philo_mtx);
}

int	get_state(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(philo->philo_mtx);
	state = philo->state;
	pthread_mutex_unlock(philo->philo_mtx);
	return (state);
}
