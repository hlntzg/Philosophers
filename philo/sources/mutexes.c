/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:22:18 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/14 09:52:46 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_print_mutex(t_data *data);
static int	init_mutex_array(t_data *data, t_mutex **mutex);

/**
 * init_mutexes - Initializes all mutexes used in the program.
 * 
 * This function initializes the three mutexes types (print, forks and philos).
 * If any initialization fails, it cleans up previously initialized mutexes
 * before returning an error.
 * 
 * Return: On success, init_mutexes returns 0; on error, it returns 1.
 */
int	init_mutexes(t_data *data)
{
	if (init_print_mutex(data) != 0)
		return (1);
	if (init_mutex_array(data, &(data->mtx->forks)) != 0)
	{
		destroy_mutexes(NULL, 0, &(data->mtx->print));
		return (1);
	}
	if (init_mutex_array(data, &(data->mtx->philos)) != 0)
	{
		destroy_mutexes(&(data->mtx->forks), data->arg.n_philo,
			&(data->mtx->print));
		return (1);
	}
	return (0);
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
	return (0);
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
	return (0);
}

/**
 * destroy_mutexes - Destroy and frees mutexes.
 *
 * @mutex_array: Pointer to an array of mutexes.
 * @i: Number of mutexes in the array to destroy.
 * @single_mutex: Pointer to a single mutex to destroy.
 *
 * It safely destroys the mutexes, frees allocated memory, and sets pointers to
 * NULL to prevent dangling references. Either mutex_array or single_mutex
 * can be NULL if not needed.
 */
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
