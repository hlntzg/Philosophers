/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:03:13 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/08 16:38:42 by hutzig           ###   ########.fr       */
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

int	ft_atoi(char *str);
size_t	ft_strlen(char *str);
void	ft_putstr_fd(char *str, int fd);

#endif
