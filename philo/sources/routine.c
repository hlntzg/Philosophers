/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:06:35 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/30 15:08:33 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_think(t_philo *philo)
{
	set_status(philo, THINKING);
	get_message(philo, NULL);
}

int	to_sleep(t_philo *philo)
{
	set_status(philo, SLEEPING);
	get_message(philo, NULL);
	ft_sleep();
}

int	to_eat(t_philo *philo)
{
	set_status(philo, EATING);
	get_message(philo, NULL);
	ft_sleep();
}
