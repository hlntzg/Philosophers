/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:03:13 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/11 17:04:00 by hutzig           ###   ########.fr       */
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

typedef enum s_status
{
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_status;

typedef struct s_philo
{
	t_status	status;
	t_time		last_meal;
	int			id;
	int			count_meal;
}	t_philo;

typedef struct s_data
{
	t_args	arg;
	t_time	start;
	t_philo	*philo;
}	t_data;

int		ft_atoi(char *str);
size_t	ft_strlen(char *str);
void	ft_putstr_fd(char *str, int fd);

unsigned long	elapsed_time(t_time start);

#endif
