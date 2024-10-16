/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:41:38 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/16 16:26:29 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// void	destroy_mutex(t_mutex **mutex, int i)

static int init_multiple_mutex(t_data *data, t_mutex **mutex)
{	
	int	i;

	*mutex = (t_mutex *)malloc((sizeof(t_mutex)) * data->arg.n_philo);
	i = 0;
	while (i++ < (*data).arg->n_philo)
	{
		if (pthread_mutex_init(&(*mutex[i]), NULL) != 0)
		{
    			ft_putstr_fd("pthread_mutex_init() failed\n", 2);
    			return (EXIT_FAILURE); // Cleanup already initialized mutexes
		}
	}
	return (EXIT_SUCCESS);
}

static int	init_philo_mutexes(t_data *data)
{
	return (init_multiple_mutex(data, &(data->mtx->philos)));
}

static int	init_forks_mutexes(t_data *data)
{
	return (init_multiple_mutex(data, &(data->mtx->forks)));
}

static int	init_print_mutex(t_data *data)
{
	data->mtx->print = (t_mutex *)malloc(sizeof(t_mutex));
	if (!data->mtx->print)
	{
    		ft_putstr_fd("Memory allocation failed\n", 2);
    		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(data->mtx->print, NULL) != 0)
	{
		free(data->mtx->print);
    		ft_putstr_fd("pthread_mutex_init() failed\n", 2);
    		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_mutexes(t_data **data)
{
	if (init_print_mutex(data))
		return (EXIT_FAILURE);
	if (init_forks_mutexes(data))
		return (EXIT_FAILURE); // Cleanup already initialized mutexes (print)
	if (init_philo_mutexes(data))
		return (EXIT_FAILURE); // Cleanup already initialized mutexes (print and forks)
}

static void	init_philo_mtx(t_data *data, t_philo *philo, int i)
{
	philo->print = &(data->mtx->print);
	if (i == 0)
        	philo->f_left = &(data->mtx->forks[data->arg.n_philo - 1]);
    	else
		philo->f_left = &(data->mtx->forks[i - 1]);
    	philo->f_right = &(data->mtx->forks[i];
/*	if (i % 2 == 0) // even philo
	{
		philo->f_right = &(data->mtx->forks[i]);
		if (i == 0)
			philo->f_left = &(data->mtx->forks[data->args.n_philo - 1]);
		else
			philo->f_left = &(data->mtx->forks[i - 1]);
	}
	else
	{
		philo->f_right = &(data->mtx->forks[i]);
		philo->f_left = &(data->mtx->forks[i - 1]);
	}
*/
}

static void	init_philosophers(t_data **data)
{
	int	i;

	i = 0;
	while (i++ < (*data).arg->n_philo)
	{
		(*data).philo[i]->id = i + 1;
		(*data).philo[i]->count_meal = 0;
		(*data).philo[i]->living_status = NOT_DEAD;
		(*data).philo[i]->status = THINK;
		(*data).philo[i]->last_meal = (*data)->start;
		init_philo_mtx(*data, &((*data)->philo[i]), i);
	}
}

int	init_data(t_data **data)
{
	(*data)->mtx = (t_mtx *)malloc(sizeof(t_mtx));
	if (!(*data)->mtx)
	{
    		ft_putstr_fd("Memory allocation failed\n", 2);
    		return (EXIT_FAILURE);
	}
	(*data)->mtx->philos = NULL;
	(*data)->mtx->forks = NULL;
	(*data)->mtx->print = NULL;
	if (init_mutexes(t_data *data))
    		return (EXIT_FAILURE);
	(*data)->philo = (t_philo *)malloc(sizeof(t_philo) * (*data)->arg.n_philo);
	if (!(*data)->philo)
	{
    		ft_putstr_fd("Memory allocation failed\n", 2);
    		return (EXIT_FAILURE);
	}
	init_philosophers(t_data data);
	return (EXIT_SUCCESS);
}
