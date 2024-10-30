/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:16:46 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/30 14:33:54 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	main(int argc, char **argv)
{
	t_data	*data;
	
	if (argc != 5 && argc != 6)
		return (error("Invalid number of argument"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (error("Memory allocation failed"));
	if (gettimeofday(&(data->start), NULL) == -1)
	{
		free(data);
		return (error("Failed to get starting time"));
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
