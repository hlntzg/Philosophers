/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:03:13 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/29 16:08:05 by hutzig           ###   ########.fr       */
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
	int	n_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_meals;
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
	EAT,
	SLEEP,
	THINK,
	NOT_DEAD,
	DEAD
}	t_status;

typedef enum s_state
{
	NOT_DEAD,
	FULL,
	OVER,
}	t_state;

typedef struct s_philo
{
	int			id;
	int			count_meal;
	int			living_status;
	t_status	status;
	t_time		last_meal;
	t_mutex		*f_right;
	t_mutex		*f_left;
	t_mutex		*print;
}	t_philo;

typedef struct s_data
{
	t_args	arg;
	t_time	start;
	t_philo	*philo;
	t_mtx	*mtx;
}	t_data;

// init
int	init_args(t_data *data, char **argv);

// utils
int		ft_atoi(char *str);
size_t	ft_strlen(char *str);
void	ft_putstr_fd(char *str, int fd);

// tools
unsigned long	elapsed_time(t_time start);

#endif
