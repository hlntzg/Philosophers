/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:16:46 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/14 09:35:15 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_args(t_data *data, char **argv);
static int	clean_up_and_exit(t_data *data, int code);

/**
 * main - Entry point of the philo program.
 * @argc: Argument count from command line.
 * @argv: Argument vector from command line.
 * 
 * This function checkes the number of command-line arguments, parses input,
 * initializes the general data structure, starts the simulation with
 * dining_philosophers(), and cleans up resources before exiting.
 */
int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (error("Invalid number of argument\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (error("Memory allocation failed\n"));
	if (init_args(data, argv))
	{
		free(data);
		return (1);
	}
	if (init_data(&data))
		return (clean_up_and_exit(data, 1));
	if (dining_philosophers(data))
		return (clean_up_and_exit(data, 1));
	return (clean_up_and_exit(data, 0));
}

/**
 * init_args - Parses and validates the command-line arguments.
 * @argv: Array of command-line argument strings.
 * @data: Pointer to the main data structure of the program.
 *
 * This function validates each argument, ensuring they are positive integers,
 * and initialize the arg structure pointed by data. If any argument is invalid,
 * it returns an error message and a non-zero value.
 * It also records the starting time of the simulation.
 * 
 * Return: On success, init_args() returns 0; on error, it returns a non-zero.
 */
static int	init_args(t_data *data, char **argv)
{
	data->arg.n_philo = ft_atoi(argv[1]);
	if (data->arg.n_philo <= 0)
		return (error("Number of philosophers: Invalid argument\n"));
	data->arg.time_to_die = ft_atoi(argv[2]);
	if (data->arg.time_to_die <= 0)
		return (error("Time to die: Invalid argument\n"));
	data->arg.time_to_eat = ft_atoi(argv[3]);
	if (data->arg.time_to_eat <= 0)
		return (error("Time to eat: Invalid argument\n"));
	data->arg.time_to_sleep = ft_atoi(argv[4]);
	if (data->arg.time_to_sleep <= 0)
		return (error("Time to sleep: Invalid argument\n"));
	data->arg.n_meals = 0;
	if (argv[5])
	{
		data->arg.n_meals = ft_atoi(argv[5]);
		if (data->arg.n_meals <= 0)
			return (error("Number of meals: Invalid argument\n"));
	}
	if (gettimeofday(&data->arg.start, NULL) == -1)
		return (error("Failed to get starting time\n"));
	return (0);
}

/**
 * clean_up_and_exit - Cleans up allocated resources and exits the program.
 * @data: Pointer to the main data structure of the program.
 * @code: The exit code to return after cleanup.
 *
 * This function releases all dynamically allocated memory and destroys
 * associated mutexes, ensuring safe termination of the program.
 *
 * Return: The provided exit code after cleanup is complete.
 */
static int	clean_up_and_exit(t_data *data, int code)
{
	if (data->mtx->print != NULL)
		destroy_mutexes(NULL, 0, &(data->mtx->print));
	if (data->mtx->forks != NULL)
		destroy_mutexes(&(data->mtx->forks), data->arg.n_philo, NULL);
	if (data->mtx->philos != NULL)
		destroy_mutexes(&(data->mtx->philos), data->arg.n_philo, NULL);
	if (data->mtx)
		free(data->mtx);
	if (data->philo)
		free(data->philo);
	free(data);
	return (code);
}
