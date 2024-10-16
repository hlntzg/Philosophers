/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:34:39 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/16 08:35:06 by hutzig           ###   ########.fr       */
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
