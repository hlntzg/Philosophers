/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:16:46 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/09 13:21:12 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data_args(t_data *data, int i, int nb)
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
		init_data_args(data, i, tmp);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Invalid number of argument\n", 2);
		return (EXIT_FAILURE);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
	{
    		ft_putstr_fd("Memory allocation failed\n", 2);
    		return (EXIT_FAILURE);
	}
	if (get_arguments(data, argc, argv))
	{
		free(data);
		return (EXIT_FAILURE);
	}
	//printf("%d\tn_philo\n", data->arg.n_philo);
	//printf("%d\ttime_to_die\n", data->arg.time_to_die);
	//printf("%d\ttime_to_eat\n", data->arg.time_to_eat);
	//printf("%d\ttime_to_sleep\n", data->arg.time_to_sleep);
	//printf("%d\tn_meals\n", data->arg.n_meals);
	free(data);
	return (EXIT_SUCCESS);
}
