/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:23:18 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/05 15:50:20 by hutzig           ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}

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
	return (EXIT_SUCCESS);
}
