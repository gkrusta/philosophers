/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:40:47 by gkrusta           #+#    #+#             */
/*   Updated: 2023/12/01 15:39:26 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	action(t_philo *p, char *str)
{
	sem_wait(p->rule->done);
	if (p->rule->dead_flag == false && p->rule->done_eating == false)
		printf("%lld %d %s\n", (get_time() - p->rule->start_t), p->id, str);
	sem_post(p->rule->done);
}

void	eat_one(t_philo *p)
{
	sem_wait(p->rule->forks);
	action(p, "has taken a fork");
	usleep(p->rule->life_t * 1000);
	sem_post(p->rule->forks);
}

void	eating(t_philo *p)
{
	t_main	*philo_eat;

	philo_eat = p->rule;
	sem_wait(philo_eat->forks);
	action(p,"has taken a fork");
	sem_wait(philo_eat->forks);
	action(p, "has taken a fork");
	sem_wait(philo_eat->eating);
	p->last_meal = get_time();
	action(p, "is eating");
	p->nb_eat++;
/* 	sem_wait(philo_eat->nb_eat);
	sem_post(philo_eat->nb_eat);//switch <-> */
	sem_post(philo_eat->eating);
	ft_usleep(philo_eat->eat_t);
	sem_post(philo_eat->forks);
	sem_post(philo_eat->forks);
}

void	routine(t_philo *p, t_main *philo)
{
	int	i;

	i = 0;
	if (pthread_create(&(philo->p_id), NULL, death_check, philo) != 0)
		printf("Error\n");
	if (philo->num_philos == 1)
		eat_one(p);
	else
	{
		while (1)
		{
			if (p->id % 2 == 0)
				usleep(100); // so the second philo doesn't take the fork of the first one
			eating(p);
			sem_wait(philo->done);
			if (philo->done_eating == true || philo->dead_flag == true)
				break ;
			sem_post(philo->done);
			action(p, "is sleeping");
			ft_usleep(philo->sleep_t);
			action(p, "is thinking");
		}
	}
	sem_post(philo->done);
	if (pthread_join(philo->p_id, NULL) != 0)
		printf("Error\n");
	exit (0);
}
