/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:23:18 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/14 10:14:57 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg);

/**
 * dining_philosopher - Implements the main dining philosophers simulation.
 * 
 * This function:
 * 1. Allocates memory for philosopher threads.
 * 2. Creates a thread for each philosopher, running the 'routine' function.
 * 3. Starts a monitoring process to oversee the simulation (main process).
 * 4. Handles thread creation errors by terminating existing threads.
 * 5. Frees allocated memory before returning.
 *
 * Return: 0 on successful completion, 1 on error (with error message printed).
 */
int	dining_philosophers(t_data *data)
{
	pthread_t	*th;
	int			i;

	th = (pthread_t *)malloc(sizeof(pthread_t) * data->arg.n_philo);
	if (!th)
		return (error("Memory allocation failed\n"));
	i = 0;
	while (i < data->arg.n_philo)
	{
		if (pthread_create(&th[i], NULL, &routine, &(data->philo[i])) != 0)
		{
			terminate_threads(data, i);
			free(th);
			return (error("Failed to create thread\n"));
		}
		data->philo[i].thread_id = th[i];
		i++;
	}
	monitoring(data);
	free(th);
	return (0);
}

/**
 * routine - Run the routine of a philosopher thread. 
 * @arg: Void pointer to the philosopher's data structure (t_philo).
 *
 * The function is designed to be used as a thread routine in pthread_create,
 * implementing the main loop for each philosopher until the simulation ends.
 * It introduces a delay for odd-numbered philosophers (and != 1) to prevent
 * deadlock on more than one thread simulation. Each philo cycles through eating,
 * sleeping, and thinking until it encountes an error or thread state is OVER.
 *
 * Return: Always returns NULL.
 */
static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0 && philo->arg.n_philo != 1)
	{
		to_think(philo);
		ft_usleep(philo, philo->arg.time_to_eat / 2);
	}
	while (get_state(philo) != OVER)
	{
		if (to_eat(philo) != 0)
			break ;
		if (to_sleep(philo) != 0)
			break ;
		to_think(philo);
	}
	return (NULL);
}

/**
 * terminate_threads - Safely terminates a specified number of threads.
 * @data: Pointer to the main data structure.
 * @nb: Number of philo threads to terminate.
 * 
 * This functions is called when the simulation must stop or to clean up threads
 * in case of an error. It performs two main tasks:
 * 1. Sets the state of 'nb' philosophers to OVER, signaling them to exit.
 * 2. Waits for these threads to complete using pthread_join.
 * 
 * Return: 0 on successful termination,; if pthread_join fails, it returns 1.
 */
int	terminate_threads(t_data *data, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		set_state(&(data->philo[i]), OVER);
		i++;
	}
	i = 0;
	while (i < nb)
	{
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
			return (error("pthread_join() failed\n"));
		i++;
	}
	return (0);
}
