/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:16:46 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/16 13:48:50 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (init_data(&data))
	//	ft_free(data);  and return ();
	// if (get_threads())
	//	ft_free(data);  and return ();
	//ft_free(data);
	return (EXIT_SUCCESS);
}
