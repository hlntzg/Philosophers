/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:06:35 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/29 18:26:22 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_think()
{
	get_status(philo, THINK);
	get_message();
}

int	to_sleep()
{
	get_status(philo, SLEEP);
	get_message();
	ft_sleep();
}

int	to_eat()
{
	get_status(philo, EAT);
	get_message();
	ft_sleep();
}

