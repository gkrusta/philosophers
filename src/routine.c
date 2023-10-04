/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:40:47 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/04 13:09:28 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action(t_philo *p, char *str)
{
	pthread_mutex_lock(&(p->rule->death));
	if (!(p->rule->dead_flag) && !(p->rule->done_eating))
		printf("%lld %d %s\n", (get_time() - p->rule->start_t), p->id, str);
	pthread_mutex_unlock(&(p->rule->death));

}

void	eat_one(t_philo *p)
{
	pthread_mutex_lock(&(p->rule->forks[p->left_f]));
	action(p, "has taken a fork");
	usleep(p->rule->life_t * 1000);
	pthread_mutex_unlock(&(p->rule->forks[p->left_f]));
}

void	*eating(t_philo *p)
{
	t_main	*philo_eat;

	philo_eat = p->rule;
	if (p->id % 2 == 1)
	{
		pthread_mutex_lock(&(philo_eat->forks[p->left_f]));
		action(p, "has taken a fork");
		if (p->right_f == -1)
			return (NULL);
		pthread_mutex_lock(&(philo_eat->forks[p->right_f]));
		action(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(philo_eat->forks[p->right_f]));
		action(p, "has taken a fork");
		pthread_mutex_lock(&(philo_eat->forks[p->left_f]));
		action(p, "has taken a fork");
	}
	pthread_mutex_lock(&(philo_eat->eating));
	p->last_meal = get_time();
	//printf("last time nb %d ate was %lld\n", p->id, p->last_meal);
	action(p, "is eating");
	pthread_mutex_lock(&(philo_eat->nb_eat));
	p->nb_eat++;
	pthread_mutex_unlock(&(philo_eat->nb_eat));
	pthread_mutex_unlock(&(philo_eat->eating));
	ft_usleep(philo_eat->eat_t);
	pthread_mutex_unlock(&(philo_eat->forks[p->right_f]));
	pthread_mutex_unlock(&(philo_eat->forks[p->left_f]));
	return (NULL);
}

void	*routine(void *void_p)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)void_p;
	i = 0;
	if (p->id % 2 == 0) // index instead of num
		usleep(1000); // so the second philo doesn't take the fork of the first one
	if (p->rule->num_philos == 1)
		eat_one(p);
	while (1)
	{
		eating(p);
		pthread_mutex_lock(&(p->rule->death));
		if (p->rule->done_eating == 1 || p->rule->dead_flag == 1)
			break;
		pthread_mutex_unlock(&(p->rule->death));
		//printf("id is %d, meals is %d and nb_eat is %d\n", p->id, p->rule->meals, p->nb_eat);
		action(p, "is sleeping");
		ft_usleep(p->rule->sleep_t);
		action(p, "is thinking");
	}
	pthread_mutex_unlock(&(p->rule->death));
	return (NULL);
}
