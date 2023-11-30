/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:40:47 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/30 18:31:40 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	action(t_philo *p, char *str)
{
	sem_wait(p->rule->done);
	if (!(p->rule->dead_flag) && !(p->rule->done_eating))
		printf("%lld %d %s\n", (get_time() - p->rule->start_t), p->id, str);
	sem_post(p->rule->done);
}

void	eat_one(t_philo *p)
{
	sem_wait(&(p->rule->forks[p->left_f]));
	action(p, "has taken a fork");
	usleep(p->rule->life_t * 1000);
	sem_post(&(p->rule->forks[p->left_f]));
}

void	eating(t_philo *p)
{
	t_main	*philo_eat;

	philo_eat = p->rule;
	sem_wait(&(philo_eat->forks[p->right_f]));
	action(p,"has taken a fork");
	sem_wait(&(philo_eat->forks[p->left_f]));
	action(p, "has taken a fork");
	sem_wait(philo_eat->eating);
	p->last_meal = get_time();
	action(p, "is eating");
	sem_wait(philo_eat->nb_eat);
	p->nb_eat++;
	sem_post(philo_eat->nb_eat);//switch <->
	sem_post(philo_eat->eating);
	ft_usleep(philo_eat->eat_t);
	sem_post(&(philo_eat->forks[p->right_f]));
	sem_post(&(philo_eat->forks[p->left_f]));
}

void	routine(t_philo *p, t_main *philo)
{
	int	i;

	i = 0;
	if (philo->num_philos == 1)
		eat_one(p);
	else
	{
		while (!philo->dead_flag)
		{
			if (p->id % 2 == 0)
				usleep(100); // so the second philo doesn't take the fork of the first one
			eating(p);
			sem_wait(philo->done);
			if (philo->done_eating == 1 || philo->dead_flag == 1)
				break;
			sem_post(philo->done);
			action(p, "is sleeping");
			ft_usleep(philo->sleep_t);
			action(p, "is thinking");
		}
	}
	//sem_post(philo->done);
	exit (0);
}
