/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:23:12 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/30 18:32:40 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	fill_philo_struct(t_main *p, int i, int j)
{
	p->philo->id = i + 1;
	p->philo->nb_eat = 0;
	p->philo->right_f = i;
	p->philo->left_f = j;
	p->philo->last_meal = get_time();
	p->philo->rule = p;
}

int	create_philos(t_main *p)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	p->philo = malloc(sizeof(t_philo) * p->num_philos);
	p->start_t = get_time();
	if (pthread_create(&(p->p_id), NULL, death_check, p) != 0)
		return (1);
	while (j < p->num_philos)
	{
		p->pid[i] = fork();
		if (p->pid[i] == -1)
			printf("Error\n");
		if (p->pid[i] == 0)
		{
			fill_philo_struct(p, i, j);
			printf("I am %i\n", p->philo->id);
			routine(p->philo, p);
		}
		i++;
		j++;
	}
	j = 0;
	p->pid[i] = fork();
	if (p->pid[i] == -1)
		printf("Error\n");
	if (p->pid[i] == 0)
	{
		fill_philo_struct(p, i, j); // for the last philospher or if there is only 1 philo
		routine(p->philo, p);
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
	sem_unlink("/forks");
	sem_unlink("/nb_eat");
	sem_unlink("/eating");
	sem_unlink("/done");
	p->pid = malloc(sizeof(pid_t) * p->num_philos);
	p->forks = sem_open("/forks", O_CREAT, 0644, p->num_philos);
	p->nb_eat = sem_open("/nb_eat", O_CREAT, 0644, 1);
	p->eating = sem_open("/nb_eat", O_CREAT, 0644, 1);
	p->done = sem_open("/done", O_CREAT, 0644, 1);
	return (0);
}
