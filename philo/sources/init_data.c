/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:41:38 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/06 09:18:48 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_philo_mtx(t_data *data, t_philo *philo, int i)
{
	philo->print = (data->mtx->print);
	philo->philo_mtx = &(data->mtx->philos[i]);
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
		(*data)->philo[i].id = i + 1;
		(*data)->philo[i].count_meal = 0;
		(*data)->philo[i].arg = (*data)->arg;
		(*data)->philo[i].state = OK;
		(*data)->philo[i].status = THINKING;
		(*data)->philo[i].last_meal.tv_sec = (*data)->arg.start.tv_sec;
		(*data)->philo[i].last_meal.tv_usec = (*data)->arg.start.tv_usec;
		set_philo_mtx(*data, &((*data)->philo[i]), i);
		i++;
	}
}

int	init_data(t_data **data)
{
	(*data)->mtx = (t_mtx *)malloc(sizeof(t_mtx));
	if (!(*data)->mtx)
		return (error("Memory allocation failed for mtx structure\n"));
	(*data)->mtx->philos = NULL;
	(*data)->mtx->forks = NULL;
	(*data)->mtx->print = NULL;
	if (init_mutexes(*data))
		return (1);
	(*data)->philo = (t_philo *)malloc(sizeof(t_philo) * (*data)->arg.n_philo);
	if (!(*data)->philo)
		return (error("Memory allocation failed for philo structure\n"));
	init_philo(data);
	return (0);
}
