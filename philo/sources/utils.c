/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:28:43 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/29 11:13:54 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* void ft_putstr_fd(char *str, int fd) {
    if (!str) {
        return; // Early exit if str is NULL
    }
    // Write the entire string in one go
    if (write(fd, str, strlen(str)) == -1) {
        // Handle write error (optional)
    }*/

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ((void) NULL);
	write(fd, str, ft_strlen(str));
}
