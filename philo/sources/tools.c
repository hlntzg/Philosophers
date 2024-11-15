/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 08:23:47 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/15 09:40:09 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/**
 * get_message - Prints a message for a philosopher's action.
 * @philo: Pointer to the philosopher structure array.
 * @str: Custom message string or NULL for default status messages.
 *
 * This function handles printing messages by using a mutex to unsure the
 * thread-safe printing. It calculates the timestamp since the start of the
 * simulation to print it with default status messages (thinking, sleeping,
 * eating) if no custom message. Ensures proper mutex unlocking after printing
 * or in case of errors.
 */
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

/**
 * set_status - Updates the status of a philosopher.
 * @philo: Pointer to the philosopher structure array.
 * @status: New status to be set.
 *
 * This function changes the status of one philosopher using mutex to ensure
 * thread-safe status update. If status is EATING, it also updates the timestamp
 * of last_meal. 
 *
 * Return: On success, set_status() returns 0; if an error occurs, it returns -1.
 */
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

void	set_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(philo->philo_mtx);
	philo->state = state;
	pthread_mutex_unlock(philo->philo_mtx);
}

int	get_status(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->philo_mtx);
	status = philo->status;
	pthread_mutex_unlock(philo->philo_mtx);
	return (status);
}

int	get_state(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(philo->philo_mtx);
	state = philo->state;
	pthread_mutex_unlock(philo->philo_mtx);
	return (state);
}
