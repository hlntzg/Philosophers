/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 08:23:47 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/11 16:30:17 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

unsigned long	elapsed_time(t_time start)
{
	t_time	end;
	unsigned long	et_sec;
	unsigned long	et_usec;

	if (gettimeofday(&end, NULL) == -1)
	{	
		ft_putstr_fd("Failed to get current time of philo action\n", 2);
		return (EXIT_FAILURE);
	}
	et_sec = (end.tv_sec - start.tv_sec);
	et_usec = (end.tv_usec - start.tv_usec);
	return (et_sec * 1000 + et_usec / 1000);
}

ft_usleep() // uslepp() is not so precise 
