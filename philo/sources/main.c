/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:16:46 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/31 17:42:52 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up_all(t_data *data)
{
	if (data->mtx->print != NULL)
		destroy_mutexes(NULL, 0, &(data->mtx->print)); 
	if (data->mtx->forks != NULL)
		destroy_mutexes(destroy_mutexes(&(data->mtx->forks), data->arg.n_philo, NULL);
	if (data->mtx->philos != NULL)
		destroy_mutexes(destroy_mutexes(&(data->mtx->philos), data->arg.n_philo, NULL);
	if (data->mtx)
		free(data->mtx);
	if (data->philo)
		free(data->mtx);
	free(data);
}	

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
	if (init_args(data, argv))
	{
		free(data);
		return (EXIT_FAILURE);
	}
	if (init_data(&data))
	{
		clean_up_all(data);
		return (EXIT_FAILURE);
	}
	if (init_dining_philosophers(data))
	{
		clean_up_all(data);
		return (EXIT_FAILURE);
	}
	clean_up_all(data);
	return (EXIT_SUCCESS);
}
/* keep in mind:
free_all: All allocated memory is properly freed.
Mutexes are destroyed before freeing any associated memory.

In main: You should free all memory (for example, data, data->mtx, data->philo, etc.) when exiting the program.
If init_data fails: Ensure to destroy any initialized mutexes and free any allocated memory before returning.
*/
