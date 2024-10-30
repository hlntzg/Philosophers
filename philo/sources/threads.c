/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:23:18 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/30 14:51:16 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
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

int	init_dining_philosophers(t_data *data)
{
	pthread_t	*th;
	int		i;

	th = (pthread_t *)malloc(sizeof(pthread) * data->n_philo);
	if (!th)
		return (error("Memory allocation failed"));
	i = 0;
	while (i < data->arg.n_philo)
	{
		if (pthread_create(&th[i], NULL, &routine, &data->philo[i]) != 0)
		{
			exit_all_threads(); //// work on this function
			return (error("Failed to create thread"));
		}
		data->philo[i].thread_id = th[i];
		i++;
	}
	monitoring(); /// work on this function
	free(th);
	return (EXIT_SUCCESS);
}
