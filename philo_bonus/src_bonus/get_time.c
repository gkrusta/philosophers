/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:34:15 by gkrusta           #+#    #+#             */
/*   Updated: 2023/12/10 12:34:42 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time(void)
{
	struct timeval	tp;
	
	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void	ft_usleep(long long int time)
{
	long long int	i;

	i = get_time();
	while (1)
	{
		if (get_time() - i >= time)
			break;
	}
}
