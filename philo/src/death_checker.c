/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:05:24 by gkrusta           #+#    #+#             */
/*   Updated: 2023/12/04 11:22:21 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_over(t_main *p, t_philo *philo)
{
	int			i;
	long long	diff;

	i = 0;
	while (i < p->num_philos && p->dead_flag == 0)
	{
		pthread_mutex_lock(&(p->eating));
		diff = get_time() - philo[i].last_meal;
		pthread_mutex_unlock(&(p->eating));
		if (diff >= p->life_t)
		{
			action(&philo[i], "died");
			pthread_mutex_lock(&(p->done));
			p->dead_flag = 1;
			pthread_mutex_unlock(&(p->done));
		}
		i++;
	}
}

void	death_check(t_main *p, t_philo *philo)
{
	int	i;

	while (p->done_eating == 0)
	{
		time_over(p, philo);
		if (p->dead_flag == 1)
			break ;
		i = 0;
		pthread_mutex_lock(&(p->nb_eat));
		while (i < p->num_philos && p->meals <= philo[i].nb_eat && p->meals != -1) // go to the next philo
			i++;
		pthread_mutex_unlock(&(p->nb_eat));
		pthread_mutex_lock(&(p->done));
		if (i == p->num_philos)
			p->done_eating = 1;
		pthread_mutex_unlock(&(p->done));
	}
}
