/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:31:33 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/05 09:42:19 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	check_dead(t_philo *philo)
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
		return (1);
	return (0);
}

static int	philos_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg.n_philo)
	{
		if (check_dead(&(data->philo[i])))
		{
			get_message(&(data->philo[i]), "died");
			terminate_threads(data, data->arg.n_philo);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	philos_full(t_data *data)
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
		if (philos_dead(data))
			break ;
		if (philos_full(data))
			break ;
	}
}
