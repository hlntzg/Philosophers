/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:34:39 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/31 17:42:34 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_data *data, char **argv)
{
	data->arg.n_philo = ft_atoi(argv[1]);
	if (data->arg.n_philo <= 0)
		return (error("Number of philosophers: Invalid argument"));
	data->arg.time_to_die = ft_atoi(argv[2]);
	if (data->arg.time_to_die <= 0)
		return (error("Time to die: Invalid argument"));
	data->arg.time_to_eat = ft_atoi(argv[3]);
	if (data->arg.time_to_eat <= 0)
		return (error("Time to eat: Invalid argument"));
	data->arg.time_to_sleep = ft_atoi(argv[4]);
	if (data->arg.time_to_sleep <= 0)
		return (error("Time to sleep: Invalid argument"));
	data->arg.n_meals = 0;
	if (argv[5])
	{
		data->arg.n_meals = ft_atoi(argv[5]);
		if (data->arg.n_meal <= 0)
			return (error("Number of meals: Invalid argument"));
	}
	return (EXIT_SUCCESS);
}

/*
static void	init_args(t_data *data, int i, int nb)
{
	if (i == 1)
		data->arg.n_philo = nb;
	else if (i == 2)
		data->arg.time_to_die = nb;
	else if (i == 3)
		data->arg.time_to_eat = nb;
	else if (i == 4)
		data->arg.time_to_sleep = nb;
	else if (i == 5)
		data->arg.n_meals = nb;
	else
		data->arg.n_meals = 0;
}

int	get_arguments(t_data *data, int argc, char **argv)
{
	int	i;
	int	tmp;

	i = 0;
	while (++i < argc)
	{
		tmp = ft_atoi(argv[i]);
		if (tmp <= 0)
		{
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd(": Invalid argument\n", 2);
			return (EXIT_FAILURE);
		}
		init_args(data, i, tmp);
	}
	return (EXIT_SUCCESS);
}*/
