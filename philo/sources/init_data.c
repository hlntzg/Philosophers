/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:41:38 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/29 16:38:56 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_philo_mtx(t_data *data, t_philo *philo, int i)
{
	philo->print = &(data->mtx->print);
    	philo->f_right = &(data->mtx->forks[i]);
	if (i == 0)
        	philo->f_left = &(data->mtx->forks[data->arg.n_philo - 1]);
    	else
		philo->f_left = &(data->mtx->forks[i - 1]);
}

static void	init_philo(t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->arg.n_philo)
	{
		(*data).philo[i]->id = i + 1;
		(*data).philo[i]->count_meal = 0;
		(*data).philo[i]->state = NOT_DEAD;
		(*data).philo[i]->status = THINK;
		(*data).philo[i]->last_meal.tv_sec = (*data)->start.tv_sec;
		(*data).philo[i]->last_meal.tv_usec = (*data)->start.tv_usec;
		set_philo_mtx(*data, &((*data)->philo[i]), i);
		i++;
	}
}

static void	destroy_mutexes(t_mutex **mutex_array, int i, t_mutex **single_mutex)
{
	if (mutex_array != NULL && *mutex_array != NULL)
	{
		while (i-- >= 0)
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

static int init_mutex_array(t_data *data, t_mutex **mutex)
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

static int	init_mutexes(t_data *data)
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
		destroy_mutexes(&(data->mtx->forks), data->arg.n_philo, &(data->mtx->print));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_data(t_data **data)
{
	(*data)->mtx = (t_mtx *)malloc(sizeof(t_mtx));
	if (!(*data)->mtx)
		return (error("Memory allocation failed for t_mtx *mtx");
	(*data)->mtx->philos = NULL;
	(*data)->mtx->forks = NULL;
	(*data)->mtx->print = NULL;
	if (init_mutexes(t_data *data))
    		return (EXIT_FAILURE);
	(*data)->philo = (t_philo *)malloc(sizeof(t_philo) * (*data)->arg.n_philo);
	if (!(*data)->philo)
		return (error("Memory allocation failed for t_philo *philo"));
	init_philo(t_data *data);
	return (EXIT_SUCCESS);
}
