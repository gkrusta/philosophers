/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:23:12 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/22 14:01:06 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_philo_struct(t_main *p, int i, int j)
{
	p->philo[i].id = i + 1;
	p->philo[i].nb_eat = 0;
	p->philo[i].right_f = i;
	p->philo[i].left_f = j;
	p->philo[i].last_meal = get_time();
	p->philo[i].rule = p;
}

int	create_philos(t_main *p)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (j < p->num_philos)
	{
		fill_philo_struct(p, i, j);
		i++;
		j++;
	}
	j = 0;
	fill_philo_struct(p, i, j); // for the last philospher and if there is only 1 of them
	return (0);
}

int	create_mutex(t_main *p)
{
	int	i;

	i = 0;
	while (i < p->num_philos)
	{
		if (pthread_mutex_init(&(p->forks[i]), NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(p->nb_eat), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(p->eating), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(p->done), NULL) != 0)
		return (1);
	return (0);
}

int	init(char **argv, t_main *p)
{
	p->num_philos = ft_atoi(argv[1]);
	p->life_t = ft_atoi(argv[2]);
	p->eat_t = ft_atoi(argv[3]);
	p->sleep_t = ft_atoi(argv[4]);
	p->done_eating = 0;
	p->dead_flag = 0;
	if (argv[5])
		p->meals = ft_atoi(argv[5]);
	else
		p->meals = -1;
	if (p->num_philos < 1 || p->num_philos > 200 || p->life_t < 1
		|| p->eat_t < 1 || p->sleep_t < 1 || p->meals < 1)
	{
		usage();
		return(1);
	}
	create_philos(p);
	create_mutex(p);
	return (0);
}
