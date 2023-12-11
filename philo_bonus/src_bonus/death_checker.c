/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:05:24 by gkrusta           #+#    #+#             */
/*   Updated: 2023/12/11 12:46:48 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	time_over(t_main *p, t_philo *philo)
{
	long long	diff;

	sem_wait(philo->eating);
	diff = get_time() - philo->last_meal;
	sem_post(philo->eating);
	if (diff >= p->life_t)
	{
		action(philo, "died");
		sem_wait(p->write);
		p->dead_flag = true;
		exit(1);
	}
	return ;
}

void	*death_check(void *void_p)
{
	t_main	*p;
	int		i;

	p = (t_main *)void_p;
	i = 0;
	while (p->done_eating == false)
	{
		time_over(p, p->philo);
		if (p->dead_flag == true)
			break ;
	}
	return (NULL);
}
