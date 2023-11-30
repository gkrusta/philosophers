/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:05:24 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/30 17:31:54 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	time_over(t_main *p, t_philo *philo)
{
	int			i;
	long long	diff;

	i = 0;
	while (i < p->num_philos && p->dead_flag == 0)
	{
		sem_wait(p->eating);
		diff = get_time() - philo[i].last_meal;
		printf("last meal time %lld    %lld\n", diff, philo[i].last_meal);
		sem_post(p->eating);
		if (diff >= p->life_t)
		{
			action(&philo[i], "died");
			sem_wait(p->done);
			p->dead_flag = 1;
			sem_post(p->done);
		}
		i++;
	}
}
void	*death_check(void *void_p)
{
	t_main	*p;
	int		i;

	p = (t_main *)void_p;
	i = 0;
	while (p->done_eating == 0)
	{
		time_over(p, p->philo);
		if (p->dead_flag == 1)
			break ;
		sem_wait(p->nb_eat);
		while (i < p->num_philos && p->meals <= p->philo[i].nb_eat && p->meals != -1) // go to the next philo
			i++;
		sem_post(p->nb_eat);
		sem_wait(p->done);
		if (i == p->num_philos)
			p->done_eating = 1;
		sem_post(p->done);
	}
	return (NULL);
}
