/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:23:18 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/29 18:26:02 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 != 0)
	{
		// to_think(); 
		// ft_usleep();
	}
	while (philo->state != OVER)
	{
		if (to_eat(philo) != 0)
			break ;
		if (to_sleep(philo) != 0)
			break ;
		to_think(philo);
	}
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
		i++;
	}
	monitoring(();
	free(th);
	return (EXIT_SUCCESS);
}
