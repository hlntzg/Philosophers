/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:23:18 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/01 10:36:20 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
	{
		to_think(philo);
		ft_usleep(philo, philo->arg.time_to_eat / 2);
	}
	while (philo->state != OVER)
	{
		if (to_eat(philo) != 0)
			break ;
		if (to_sleep(philo) != 0)
			break ;
		to_think(philo);
	}
	return (NULL);
}

static int	terminate_threads(t_data *data, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		set_state(&(data->philo[i]), OVER);
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
			return (error("pthread_join() failed"));
		i++;
	}
	return (0);
}

int	dining_philosophers(t_data *data)
{
	pthread_t	*th;
	int		i;

	th = (pthread_t *)malloc(sizeof(pthread_t) * data->arg.n_philo);
	if (!th)
		return (error("Memory allocation failed"));
	i = 0;
	while (i < data->arg.n_philo)
	{
		if (pthread_create(&th[i], NULL, &routine, &(data->philo[i])) != 0)
		{
			terminate_threads(data, i);
			free(th);
			return (error("Failed to create thread"));
		}
		data->philo[i].thread_id = th[i];
		i++;
	}
	monitoring(data);
	free(th);
	return (EXIT_SUCCESS);
}

/* monitoring functions */

int	check_dead(t_philo *philo)
{
	t_time	last_meal_time;
	long	starving_time;
	
	pthread_mutex_lock(philo->philo_mtx);
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(philo->philo_mtx);
	starving_time = elapsed_time(last_meal_time);
	if (starving_time == -1)
		return (-1);
	if (starving_time > philo->arg.time_to_die)
	{
		get_message(philo, "died");
		return (1);
	}
	return (0);
}

int	philos_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg.n_philo)
	{
		if (check_dead(&(data->philo[i])))
		{
			terminate_threads(data, data->arg.n_philo);
			return (1);
		}
		i++;
	}
	return (0);	
}

int	philos_full(t_data *data)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < data->arg.n_philo)
	{
		if (get_state(&(data->philo[i])) == FULL)
			full++;	
		i++;
	}
	if (full == data->arg.n_philo)
	{
		terminate_threads(data, data->arg.n_philo);
		return (1);
	}
	return (0);
}

void	monitoring(t_data *data)
{
	while (1)
	{
		if (philos_dead(data) || philos_full(data))
			break ;
	}
}
