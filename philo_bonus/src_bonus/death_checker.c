/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:05:24 by gkrusta           #+#    #+#             */
/*   Updated: 2023/12/01 17:02:15 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	time_over(t_main *p, t_philo *philo)
{
	long long	diff;

		sem_wait(p->eating);
		diff = get_time() - philo->last_meal;
		sem_post(p->eating);
		if (diff >= p->life_t)
		{
			action(philo, "died");
			sem_wait(p->done);
			p->dead_flag = true;
			sem_post(p->done);
		}
		return ;
}

void	*death_check(void *void_p)
{
	t_main	*p;
	int		i;

	p = (t_main *)void_p;
	i = 0;
	while (1)
	{
		time_over(p, p->philo);
		if (p->dead_flag == true) // dr 1
			break ;
		sem_wait(p->done);
		if (p->philo->nb_eat == p->meals)
		{
			p->done_eating = true;
			break ;
		}
		sem_post(p->done);
	}
	sem_post(p->done);
	return (NULL);
}
