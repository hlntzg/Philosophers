/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:03:13 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/07 08:54:34 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/**
 * stdio.h	: printf,
 * unistd.h	: write, usleep
 * stdlib.h	: malloc, free
 * pthread.h	: thread functions 
 * sys/time.h	: gettimeofday, timeval
 */
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mutex;

/**
 * @n_philo: number of philos and forks (must be > 0).
 * @time_to_die: @time_to_eat: @time_to_sleep: time in ms used for simulation.
 * @n_meals: (optional) mininum meals for each philo to stop the simulation.
 * @start: the starting time of the simulation in ms.
 */
typedef struct s_args
{
	int		n_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_meals;
	t_time	start;
}	t_args;

/**
 * status of philo's action on their routine.
 * each philo will have their own status updated.
 */
typedef enum s_status
{
	EATING,
	SLEEPING,
	THINKING,
}	t_status;

/**
 * state of the thread regarding the simulation:
 * @OK: thread is ready to be initialized.
 * @FULL: the specific philo is full and this thread can be stopped.
 * @OVER: all threads are full or some philo died, simulation must stop.
 */
typedef enum s_state
{
	OK,
	FULL,
	OVER,
}	t_state;

/**
 * @philos: array of mutexes for philosophers.
 * @forks: array of mutexes for forks, same size of philos.
 * @print: single mutex for printing.
 */
typedef struct s_mtx
{
	t_mutex	*philos;
	t_mutex	*forks;
	t_mutex	*print;
}	t_mtx;

/**
 * @id: number of philo from 1 to arg->n_philo.
 * @count_meal: number of times each philo has eaten. 
 * @thread_id: thread handle id.
 * @arg: pointer to the simulation parameters.
 * @status: philo's status (eating, sleeping, thinking).
 * @state: philo's thread state (ok, full, over).
 * @last_meal: initial time of last meal.
 * @philo_mtx: pointer to the philosopher's individual mutex.
 * @print: pointer to the global print mutex.
 * @f_right: pointer to the mutex representing the right fork.
 * @f_left: pointer to the mutex representing the left fork.
 */
typedef struct s_philo
{
	int			id;
	int			count_meal;
	pthread_t	thread_id;
	t_args		arg;
	t_status	status;
	t_state		state;
	t_time		last_meal;
	t_mutex		*philo_mtx;
	t_mutex		*print;
	t_mutex		*f_right;
	t_mutex		*f_left;
}	t_philo;

/**
 * @arg: simulation parameters and start time.
 * @philo: array of philosophers' structure (philo's data).
 * @mtx: pointer to mutexes used for synchronization.
 */
typedef struct s_data
{
	t_args	arg;
	t_philo	*philo;
	t_mtx	*mtx;
}	t_data;

/** init_data.c and mutexes.c
 * initialize philo and mtx structs from t_data *data.
 * destroy mutexes by the end of the simulation or if a failure occur.
 */
int		init_data(t_data **data);
int		init_mutexes(t_data *data);
void	destroy_mutexes(t_mutex **mutex_array, int i, t_mutex **single_mutex);

/** threads.c and monitoring.c
 * create threads and start the simulation with the philosophers' routine.
 * monitor the philo's routine.
 */
int		dining_philosophers(t_data *data);
void	monitoring(t_data *data);
int		terminate_threads(t_data *data, int nb);

/** routine.c
 * philo's alternatively perform the actions: to_eat, to_sleep, to_think
 */
void	to_think(t_philo *philo);
int		to_sleep(t_philo *philo);
int		to_eat(t_philo *philo);
int		get_the_forks(t_philo *philo);
void	let_the_forks(t_philo *philo);

/** tools.c and time.c
 * tools and time functions to assist the philo's routine actions
 * set and get values to state and status with mutex management
 */
int		set_status(t_philo *philo, t_status status);
int		get_status(t_philo *philo);
void	get_message(t_philo *philo, char *str);
void	set_state(t_philo *philo, t_state state);
int		get_state(t_philo *philo);
long	elapsed_time(t_time start);
int		ft_sleep(t_philo *philo, long time);

/** utils.c */
int		error(char *str);
int		ft_atoi(char *str);

#endif
