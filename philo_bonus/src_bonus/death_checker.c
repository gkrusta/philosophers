/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:05:24 by gkrusta           #+#    #+#             */
/*   Updated: 2023/12/06 16:59:55 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	time_over(t_main *p, t_philo *philo)
{
	long long	diff;

	sem_wait(philo->eating);
	diff = get_time() - philo->last_meal; // dr 2
	sem_post(philo->eating);
	if (diff >= p->life_t)
	{
		action(philo, "died");
		sem_wait(p->write);
		sem_wait(p->done);
		p->dead_flag = true; // dr 3
		sem_post(p->done);
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
		if (p->dead_flag == true) // dr 1
			break ;
	}
	return (NULL);
}
