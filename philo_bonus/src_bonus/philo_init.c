/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:23:12 by gkrusta           #+#    #+#             */
/*   Updated: 2023/12/10 12:45:50 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	err(char *str)
{
	while (*str)
		write (2, str++, 1);
	return (1);
}

void	fill_philo_struct(t_main *p, int i)
{
	char	*name;

	p->philo->id = i + 1;
	name = ft_itoa(p->philo->id);
	p->philo->nb_eat = 0;
	p->philo->last_meal = get_time();
	p->philo->rule = p;
	sem_unlink(name);
	p->philo->eating = sem_open(name, O_CREAT, 0700, 1);
	p->start_t = get_time();
	free (name);
}

int	create_philos(t_main *p)
{
	int	i;

	i = 0;
	p->philo = malloc(sizeof(t_philo) * p->num_philos);
	if (p->philo == NULL)
		return(err("error: fatal\n"));
	while (i < p->num_philos)
	{
		p->pid[i] = fork();
		if (p->pid[i] == -1)
			return (err("error while creating forks\n"));
		else if (p->pid[i] == 0)
		{
			fill_philo_struct(p, i);
			routine(p->philo, p);
		}
		i++;
	}
	return (0);
}

int	init(char **argv, t_main *p)
{
	p->num_philos = ft_atoi(argv[1]);
	p->life_t = ft_atoi(argv[2]);
	p->eat_t = ft_atoi(argv[3]);
	p->sleep_t = ft_atoi(argv[4]);
	p->done_eating = false;
	p->dead_flag = false;
	if (argv[5])
		p->meals = ft_atoi(argv[5]);
	else
		p->meals = -1;
	if (p->num_philos < 1 || p->num_philos > 200 || p->life_t < 1
		|| p->eat_t < 1 || p->sleep_t < 1)
		return (usage());
	sem_unlink("/forks");
	sem_unlink("/write");
	//sem_unlink("/eating");
	sem_unlink("/done");
	p->pid = malloc(sizeof(pid_t) * p->num_philos);
	p->forks = sem_open("/forks", O_CREAT, 0644, p->num_philos);
	p->write = sem_open("/write", O_CREAT, 0644, 1);
	//p->eating = sem_open("/eating", O_CREAT, 0644, 1);
	p->done = sem_open("/done", O_CREAT, 0644, 1);
	return (0);
}
