/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:23:18 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/22 08:47:40 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_up_threads(t_data *data)
{
	pthread_t	*th;
	int		i;

	th = (pthread_t *)malloc(sizeof(pthread) * data->n_philo);
	if (!th)
	{
    		ft_putstr_fd("Memory allocation failed\n", 2);
    		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&th[i], NULL, *new_routine, &data->philo[i]) != 0)
		{
    			ft_putstr_fd("Pthread failed to be created\n", 2);
			free(th);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
