/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:16:46 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/11 09:24:44 by hutzig           ###   ########.fr       */
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
	if (gettimeofday(&(data->start), NULL) == -1)
	{
    		ft_putstr_fd("Failed to get starting time\n", 2);
		free(data);
		return (EXIT_FAILURE);
	}
	if (get_arguments(data, argc, argv))
	{
		free(data);
		return (EXIT_FAILURE);
	}
	printf("%ld data->start as the entry point of the program\n", data->start.tv_sec);
	free(data);
	return (EXIT_SUCCESS);
}
