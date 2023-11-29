/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:23:12 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/29 15:53:35 by gkrusta          ###   ########.fr       */
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
		p->pid[i] = fork();
		if (p->philo[i].id == -1)
			printf("Error\n");
		if (p->philo[i].pid == 0)
		{
			fill_philo_struct(p, i, j);
			i++;
			j++;
			philospher_routine(p);
		}
	}
	j = 0;
	p->pid[i] = fork();
	if (p->philo[i].id == -1)
		printf("Error\n");
	if (p->philo[i].pid == 0)
	{
		fill_philo_struct(p, i, j); // for the last philospher or if there is only 1 philo
		philospher_routine(p);
	}
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
		|| p->eat_t < 1 || p->sleep_t < 1)
	{
		usage();
		return (1);
	}
	p->pid = malloc(sizeof(pid_t) * p->num_philos);
	p->forks = ("&FORKS", O_CREAT, );
	return (0);
}
