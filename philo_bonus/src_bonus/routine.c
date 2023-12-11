/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:40:47 by gkrusta           #+#    #+#             */
/*   Updated: 2023/12/10 18:34:45 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	action(t_philo *p, char *str)
{
	sem_wait(p->rule->done);
	if (!p->rule->done_eating)
	{
		sem_wait(p->rule->write);
		printf("%lld %d %s\n", (get_time() - p->rule->start_t), p->id, str);
		sem_post(p->rule->write);
	}
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
	action(p, "has taken a fork");
	sem_wait(philo_eat->forks);
	action(p, "has taken a fork");
	sem_wait(p->eating);
	p->last_meal = get_time();
	sem_post(p->eating);
	action(p, "is eating");
	sem_wait(philo_eat->done);
	p->nb_eat++;
	if (p->nb_eat >= philo_eat->meals && philo_eat->meals != -1)
		philo_eat->done_eating = true;
	sem_post(philo_eat->done);
	ft_usleep(philo_eat->eat_t);
	sem_post(philo_eat->forks);
	sem_post(philo_eat->forks);
}

void	routine(t_philo *p, t_main *philo)
{
	int	i;

	i = 0;
	if (pthread_create(&(philo->p_id), NULL, death_check, philo) != 0)
		err("error: fatal\n");
	if (philo->num_philos == 1)
		eat_one(p);
	else
	{
		while (philo->dead_flag == false)
		{
			eating(p);
			sem_wait(philo->done);
			if (philo->done_eating == true)
				break ;
			sem_post(philo->done);
			action(p, "is sleeping");
			ft_usleep(philo->sleep_t);
			action(p, "is thinking");
		}
		sem_post(philo->done);
	}
	if (pthread_join(philo->p_id, NULL) != 0)
		err("error: fatal\n");
	exit (0);
}
