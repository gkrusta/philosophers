/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:05:24 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/04 13:07:22 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_check(t_main *p, t_philo *philo)
{
	int			i;
	long long	diff;

	//i = 0;
	while (p->done_eating == 0)
	{
		//printf("hello from death check\n");
		i = 0;
		while (i < p->num_philos && p->dead_flag == 0)
		{
			pthread_mutex_lock(&(p->eating));
			diff = get_time() - philo[i].last_meal;
			//printf("* counter i is %d, id %d*, diff is %lld and last meals was %lld and life_t is %d\n", i, philo[i].id, diff, philo[i].last_meal, p->life_t);
			pthread_mutex_unlock(&(p->eating));
			if (diff >= p->life_t)
			{
 				action(&philo[i], "died");
				pthread_mutex_lock(&(p->death));
				p->dead_flag = 1;
				pthread_mutex_unlock(&(p->death));
			}
			i++;
			usleep(100);
		}
		if (p->dead_flag == 1)
			break ;
		//i--;
		//printf("id is %d, meals is %d and nb_eat is %d\n", philo[i].id, p->meals, philo[i].nb_eat);
		i = 0;
		pthread_mutex_lock(&(p->nb_eat));
		while (i < p->num_philos && p->meals <= philo[i].nb_eat && p->meals != -1) // go to the next philo
			i++;
		pthread_mutex_unlock(&(p->nb_eat));
		//printf("i = %d\n", i);
		pthread_mutex_lock(&(p->death));
		if (i == p->num_philos)
			p->done_eating = 1;
		pthread_mutex_unlock(&(p->death));
	}
}
