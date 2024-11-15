/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:06:35 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/14 17:33:18 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * to_think - Thinking action of philo routine.
 * @philo: Pointer to a specific philo in the structure array of philosophers.
 * 
 * The function sets the philosopher's status to THINKING and prints the message
 * about the change of its status with the timestamp in miliseconds.
 */
void	to_think(t_philo *philo)
{
	set_status(philo, THINKING);
	get_message(philo, NULL);
}

/**
 * to_sleep - Sleeping action of philo routine.
 * @philo: Pointer to a specific philo in the structure array of philosophers.
 * 
 * The function sets the philosopher's status to SLEEPING, prints the message
 * about the change of its status with the timestamp in miliseconds, and calls
 * the custom sleep() to suspend the execution of the current thread.
 *
 * Return: 0 if the requested time has elapsed; On failure, it returns -1.
 */
int	to_sleep(t_philo *philo)
{
	set_status(philo, SLEEPING);
	get_message(philo, NULL);
	if (ft_sleep(philo, philo->arg.time_to_sleep) != 0)
		return (-1);
	return (0);
}

/**
 * to_eat - Eating action of philo routine.
 * @philo: Pointer to a specific philo in the structure array of philosophers.
 * 
 * Before setting the status to EATING and printing the message, the function 
 * calls get_the_forks() that attempts to acquire the shared resources by 
 * threads. The thread is suspended for the duration of time_to_eat. It releases
 * the forks and tracks the meal count, updating the thread state to
 * FULL if the eating has occured the same number of times of n_meals.
 *
 * Return: 0 on successful eating, -1 if any step fails.
 */
int	to_eat(t_philo *philo)
{
	if (get_the_forks(philo) != 0)
		return (-1);
	set_status(philo, EATING);
	get_message(philo, NULL);
	if (ft_sleep(philo, philo->arg.time_to_eat) != 0)
		return (-1);
	let_the_forks(philo);
	pthread_mutex_lock(philo->philo_mtx);
	philo->count_meal++;
	if (philo->count_meal == philo->arg.n_meals)
		philo->state = FULL;
	pthread_mutex_unlock(philo->philo_mtx);
	return (0);
}

/**
 * get_the_forks - Attempts to acquire forks for a philosopher.
 * @philo: Pointer to the philosopher structure.
 *
 * This function implements the fork acquisition process:
 * 1. Locks the right fork first. Unlock the resource if the simulation is over.
 * 2. Gets the message "has taken a fork".
 * 3. Handles the special case of only one philosopher.
 * 4. Locks the left fork and checks if the simulation is over.
 * 5. Gets the message "has taken a fork" for the second fork.
 * 5. Ensures forks are released if the simulation ends during acquisition.
 *
 * @return: 0 if both forks are successfully acquired; Otherwise it returns -1.
 */
int	get_the_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->f_right);
	if (get_state(philo) == OVER)
	{
		pthread_mutex_unlock(philo->f_right);
		return (-1);
	}
	get_message(philo, "has taken a fork");
	if (philo->arg.n_philo == 1)
	{
		pthread_mutex_unlock(philo->f_right);
		return (-1);
	}
	pthread_mutex_lock(philo->f_left);
	if (get_state(philo) == OVER)
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
