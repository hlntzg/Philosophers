/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:03:13 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/04 11:17:52 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/**
 * string.h 	: memset,
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

typedef struct s_args
{
	int		n_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_meals;
	t_time	start;
}	t_args;

typedef pthread_mutex_t	t_mutex;

typedef struct s_mtx
{
	t_mutex	*philos;	// Array of mutexes for philosophers
	t_mutex	*forks;		// Array of mutexes for forks
	t_mutex	*print;		// Single mutex for printing
}	t_mtx;

typedef enum s_status
{
	EATING,
	SLEEPING,
	THINKING,
}	t_status;

typedef enum s_state
{
	LIVING,
	FULL,
	OVER,
}	t_state;

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

typedef struct s_data
{
	t_args	arg;
	t_philo	*philo;
	t_mtx	*mtx;
}	t_data;

// init
int	init_data(t_data **data);
int	init_mutexes(t_data *data);
void	destroy_mutexes(t_mutex **mutex_array, int i, t_mutex **single_mutex);


int	dining_philosophers(t_data *data);

// could be monitoring .c file
void	monitoring(t_data *data);
int	philos_full(t_data *data);
int	philos_dead(t_data *data);
int	check_dead(t_philo *philo);

// routine
void	to_think(t_philo *philo);
int		to_sleep(t_philo *philo);
int		to_eat(t_philo *philo);
int		get_the_forks(t_philo *philo);
void	let_the_forks(t_philo *philo);

// tools
int		set_status(t_philo *philo, t_status status);
int		get_status(t_philo *philo);
void	get_message(t_philo *philo, char *str);
void	set_state(t_philo *philo, t_state state);
int		get_state(t_philo *philo);

// time
long	elapsed_time(t_time start);
int	ft_usleep(t_philo *philo, long time);

// utils
int		ft_atoi(char *str);
void	ft_putstr_fd(char *str, int fd);

int	error(char *str);

#endif
