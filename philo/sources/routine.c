/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:06:35 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/31 09:56:06 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_think(t_philo *philo)
{
	set_status(philo, THINKING);
	get_message(philo, NULL); // should check for faild on gettimeofday?
}

int	to_sleep(t_philo *philo)
{
	set_status(philo, SLEEPING);
	get_message(philo, NULL);
	if (ft_sleep(philo->arg.time_to_sleep) != 0)
		return (-1);
}

int	get_state(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(philo->philo_mtx);
	state = philo->state;
	pthread_mutex_unlock(philo->philo_mtx);
	return (state);
}
int	get_the_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->f_right);
	if (get_state(philo) == FULL)
	{
		pthread_mutex_unlock(philo->f_right);
		return (-1);
	}
	get_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->f_left);
	if (get_state(philo) == FULL)
	{
		let_the_forks(philo);
		return (-1);
	}
	get_message(philo, "has taken a fork");
	return (0);
}

void	let_the_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->f_right);
	pthread_mutex_unlock(philo->f_left);
}

int	to_eat(t_philo *philo)
{
	if (get_the_forks(philo) != 0)
		return (-1);
	set_status(philo, EATING);
	get_message(philo, NULL);
	if (ft_sleep(philo->arg.time_to_eat) != 0)
		return (-1);
	let_the_forks(philo);
	pthread_mutex_lock(philo->philo_mtx);
	philo->count_meal++;
	if (philo->count_meal == philo->arg.n_meals)
		philo->state = FULL;
	pthread_mutex_unlock(philo->philo_mtx);
	return (0);
}
