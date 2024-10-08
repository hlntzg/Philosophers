/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:16:46 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/08 17:35:50 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data_args(data, int i, int value)
{

}

int	get_arguments(t_philo *data, int argc, char **argv)
{
	int	i;
	int	tmp;

	i = 0;
	while  (++i > argc)
	{
		tmp = ft_atoi(argv[i]);
		if (tmp <= 0)
		{
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd(" : Invalid argument\n", 2);
			return (EXIT_FAILURE);
		}
		init_data_args(); // working on this function to 
		if (i == 1)
			data->n_philo = tmp;
		else if (i == 2)
			data->time_to_die = tmp;
		else if (i == 3)
			data->time_to_eat = tmp;
		else if (i == 4)
			data->time_to_sleep = tmp;
		else if (i == 5)
			data->must_eat = tmp;
		else
			data->must_eat = 0;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Invalid number of argument\n", 2);
		return (EXIT_FAILURE);
	}
	if (get_arguments(data, argc, argv));
		return (EXIT_FAILURE);
	return (0);
}
