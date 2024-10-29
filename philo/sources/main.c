/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:16:46 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/29 18:07:00 by hutzig           ###   ########.fr       */
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
	if (init_args(data, argv) != 0)
	{
		free(data);
		return (EXIT_FAILURE);
	}
	if (init_data(&data) != 0)
	{
	//	ft_free(data); //free everyhing and destroy mutexes! 
		return (EXIT_FAILURE);
	}
	if (init_dining_philosophers(data)!= 0)
	//{
	//	ft_free(data);
	//	return (EXIT_FAILURE);
	//}
	//ft_free(data);
	return (EXIT_SUCCESS);
}
/* keep in mind:
ft_free: All allocated memory is properly freed.
Mutexes are destroyed before freeing any associated memory.

In main: You should free all memory (for example, data, data->mtx, data->philo, etc.) when exiting the program.
If init_data fails: Ensure to destroy any initialized mutexes and free any allocated memory before returning.
*/
