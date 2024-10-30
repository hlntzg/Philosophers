/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 08:23:47 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/30 16:34:22 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long	elapsed_time(t_time start)
{
	t_time	end;
	long	et_sec;
	long	et_usec;

	if (gettimeofday(&end, NULL) == -1)
		return (-1);
	et_sec = (end.tv_sec - start.tv_sec);
	et_usec = (end.tv_usec - start.tv_usec);
	return (et_sec * 1000 + et_usec / 1000);
}

int	ft_usleep(t_philo *philo, long time)
{
	t_time	s_start;
	long	current;

	if (gettimeofday(&s_start, NULL) == -1)
		return (error("gettimeofday() failed on ft_usleep"));
	while (1)
	{
		current = elapsed_time(s_start);
		if (current == -1)
			return (error("elapsed_time() failed"));
		if (current >= time)
			break ;
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

int	error(char *str)
{
	ft_putstr_fd(str, 2);
	return (EXIT_FAILURE);
}

void	set_status(t_philo *philo, t_status status)
{
	pthread_mutex_lock(philo->philo_mtx);
	philo->status = status;
	pthread_mutex_unlock(philo->philo_mtx);
}

void	get_message(t_philo *philo, char *str)
{
	char	*info;
	long	timestamp;

	pthread_mutex_lock(philo->print);
	timestamp = elapsed_time(); // need to get time passed since data->start, but we dont share t_data here of before!
	if (str)
		printf();
	else
	{
		if (philo->status == THINKING)
			info = "is thinking";
		else if (philo->status == SLEEPING)
			info = "is sleeping";
		else if (philo->status == EATING)
			info = "is eating";
		printf();
	}
	pthread_mutex_lock(philo->print);
}
