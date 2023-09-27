/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:23:12 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/27 16:12:12 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(char **argv, t_main *p)
{
	p->num_philos = ft_atoi(argv[1]);
	p->life_t = ft_atoi(argv[2]);
	p->eat_t = ft_atoi(argv[3]);
	p->sleep_t = ft_atoi(argv[4]);
	if (argv[5])
	{
		p->meals = ft_atoi(argv[5]);
		if (p->meals < 1)
			return (1);
	}
	else
		p->meals = -1;
	if (p->num_philos < 1 || p->life_t <= 0 || p->eat_t <= 0 || p->sleep_t <= 0)
	{
		//free(p);
		//usage();
		return(1);
	}
	create_philos(p);
	create_mutex(p);
	return (0);
}

int	create_philos(t_main *p)
{
	int	i;
	int	j;

/* 	p->philo = malloc(sizeof(t_philo) * (p->num_philos));
	if (p->philo == NULL)
		return (1); */
	i = 0;
	j = 1;
	while (j < p->num_philos)
	{
		fill_philo_struct(p, i, j);
		i++;
		j++;
	}
	j = 0;
	fill_philo_struct(p, i, j);
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
	if (pthread_mutex_init(&(p->write), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(p->eating), NULL) != 0)
		return (1);
	return (0);
}

void	fill_philo_struct(t_main *p, int i, int j)
{
	p->philo[i].id = i + 1;
	p->philo[i].nb_eat = 0;
	p->philo[i].left_f = i;
	p->philo[i].right_f = j;
	p->philo[i].last_meal = 0;
	p->philo[i].rule = p;
}
