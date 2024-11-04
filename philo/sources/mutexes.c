/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:22:18 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/04 14:02:04 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_mutex **mutex_array, int i, t_mutex **single_mutex)
{
	if (mutex_array != NULL && *mutex_array != NULL)
	{
		while (i-- > 0)
			pthread_mutex_destroy(&(*mutex_array)[i]);
		free(*mutex_array);
		*mutex_array = NULL;
	}
	if (single_mutex != NULL && *single_mutex != NULL)
	{
		pthread_mutex_destroy(*single_mutex);
		free(*single_mutex);
		*single_mutex = NULL;
	}
}

static int	init_mutex_array(t_data *data, t_mutex **mutex)
{
	int	i;

	*mutex = (t_mutex *)malloc((sizeof(t_mutex)) * data->arg.n_philo);
	if (!(*mutex))
		return (error("Memory allocation failed for mutexes\n"));
	i = 0;
	while (i < data->arg.n_philo)
	{
		if (pthread_mutex_init(&(*mutex)[i], NULL) != 0)
		{
			destroy_mutexes(mutex, i, NULL);
			return (error("pthread_mutex_init() failed\n"));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	init_print_mutex(t_data *data)
{
	data->mtx->print = (t_mutex *)malloc(sizeof(t_mutex));
	if (!data->mtx->print)
		return (error("Memory allocation failed for print_mutex\n"));
	if (pthread_mutex_init(data->mtx->print, NULL) != 0)
	{
		free(data->mtx->print);
		data->mtx->print = NULL;
		return (error("pthread_mutex_init() failed for print_mutex\n"));
	}
	return (EXIT_SUCCESS);
}

int	init_mutexes(t_data *data)
{
	if (init_print_mutex(data) != 0)
		return (EXIT_FAILURE);
	if (init_mutex_array(data, &(data->mtx->forks)) != 0)
	{
		destroy_mutexes(NULL, 0, &(data->mtx->print));
		return (EXIT_FAILURE);
	}
	if (init_mutex_array(data, &(data->mtx->philos)) != 0)
	{
		destroy_mutexes(&(data->mtx->forks), data->arg.n_philo,
			&(data->mtx->print));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
