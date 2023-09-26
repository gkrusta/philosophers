/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:40:47 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/26 17:01:39 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	tp;
	
	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void	*eating(t_philo *p)
{
	pthread_mutex_lock(&p->rule->forks[p->left_f]);
	printf("%lld %d %s\n", (get_time() - p->rule->start_t), p->id, "has taken a fork");
	pthread_mutex_lock(&p->rule->forks[p->right_f]);
	printf("%lld %d %s\n", (get_time() - p->rule->start_t), p->id, "has taken a fork");
	printf("%lld %d %s\n", (get_time() - p->rule->start_t), p->id, "is eating");
	p->last_meal = get_time();
	usleep (p->rule->eat_t * 1000);
	pthread_mutex_unlock(&p->rule->forks[p->left_f]);
	pthread_mutex_unlock(&p->rule->forks[p->right_f]);
	pthread_mutex_lock(&p->rule->eating);
	p->nb_eat++;
	pthread_mutex_unlock(&p->rule->eating);
}

void	*routine(void *void_p)
{
	t_philo	*p;
	int		i;

	p = void_p;
	i = 0;
	if (p->rule->num_philos % 2 == 0)
		usleep(1000); // so the second philo doesn't take the fork of the first one
	while (!p->rule->dead_flag)
	{
		eating(p);
		if ()
			break;
	}
	return (NULL);
}

int	start(t_main *p)
{
	int	i;

	i = 0;
	p->start_t = get_time();
	while (i < p->num_philos)
	{
		if (pthread_create(&(p->philo[i].id), NULL, routine, &p->philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	*p;

	if (argv_check(argv) == 1 || argc < 5 || argc > 7)
	{
		usage();
		return (1);
	}
	if (init(argv, p) == 1);
	{
		usage();
		return (1);
	}
	start(p);
	return (0);
}
