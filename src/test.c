/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:40:47 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/30 19:23:31 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time(void)
{
	struct timeval	tp;
	
	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void	action(t_philo *p, int c)
{
	pthread_mutex_lock(&(p->rule->write));
	if (c == 'f')
		printf("%lld  %d %s\n", (get_time() - p->rule->start_t), p->id, "has taken a fork");
	if (c == 'e')
		printf("%lld  %d %s\n", (get_time() - p->rule->start_t), p->id, "is eating");
	if (c == 's')
		printf("%lld  %d %s\n", (get_time() - p->rule->start_t), p->id, "is sleeping");
	if (c == 't')
		printf("%lld  %d %s\n", (get_time() - p->rule->start_t), p->id, "is thinking");
	if (c == 'd')
		printf("%lld  %d %s\n", (get_time() - p->rule->start_t), p->id, "died");
	pthread_mutex_unlock(&(p->rule->write));

}

void	*eating(t_philo *p)
{
/* 	t_philo	*philo;

	philo = p->rule; */
	if (p->id % 2 == 1)
	{
		pthread_mutex_lock(&(p->rule->forks[p->left_f]));
		action(p, 'f');
		pthread_mutex_lock(&(p->rule->forks[p->right_f]));
		action(p, 'f');
	}
	else
	{
		pthread_mutex_lock(&(p->rule->forks[p->right_f]));
		action(p, 'f');
		pthread_mutex_lock(&(p->rule->forks[p->left_f]));
		action(p, 'f');
	}
	pthread_mutex_lock(&(p->rule->eating));
	p->last_meal = get_time();
	action(p, 'e');
	p->nb_eat++;
	pthread_mutex_unlock(&(p->rule->eating));
	ft_usleep(p->rule->dead_flag, p->rule->eat_t * 1000);
	pthread_mutex_unlock(&(p->rule->forks[p->right_f]));
	pthread_mutex_unlock(&(p->rule->forks[p->left_f]));

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
	while (p->rule->dead_flag == 0 || p->nb_eat < p->rule->meals)
	{
		eating(p);
/* 		if (p->rule->dead_flag == 1)
			break; */
		action(p, 's');
		ft_usleep(p->rule->dead_flag, p->rule->sleep_t * 1000);
		action(p, 't');
	}
	return (NULL);
}

//here :**
void	death_check(t_main *p, t_philo *philo)
{
	int	i;
	int	all_eaten;

	i = 0;
	all_eaten = p->meals;
	while (all_eaten < p->meals)
	{
		while (i < p->num_philos && p->dead_flag == 0)
		{
			pthread_mutex_lock(&(p->eating));
			if (get_time() - philo[i].last_meal > p->life_t)
			{
				action(philo, 'd');
				p->dead_flag = 1;
			}
			pthread_mutex_unlock(&(p->eating));
			i++;
			usleep(50);
		}
		all_eaten--;
	}
}

int	start(t_main *p)
{
	int	i;

	i = 0;
	p->start_t = get_time();
	while (i < p->num_philos)
	{
		if (pthread_create(&(p->philo[i].p_id), NULL, routine, &(p->philo[i])) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < p->num_philos)
	{
		if (pthread_join(p->philo[i].p_id, NULL) != 0)
			return (1);
		i++;
	}
	death_check(p, p->philo);
/* 	i = 0;
	while (i < p->num_philos)
	{
		destroy fork mutex. write and eat mutexx after..
	} */
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	*p;

	p = malloc(sizeof(t_main));
	if (argv_check(argv) == 1 || argc < 5 || argc > 7)
	{
		printf("argv: %s %s %s %s %s and argc is %d\n", argv[1], argv[2], argv[3], argv[4], argv[5], argc);
		usage();
		return (1);
	}
	if (init(argv, p) == 1)
	{
		usage();
		return (1);
	}
	start(p);
	return (0);
}
