/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:53:50 by gkrusta           #+#    #+#             */
/*   Updated: 2023/12/10 13:16:12 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	close_semaphores(t_main *p)
{
	int	i;

	i = 0;
	while (i < p->num_philos)
	{
		if (sem_close(&(p->forks[i])) != 0)
			return (1);
		i++;
	}
	if (sem_close(p->write) != 0)
		return (1);
	if (sem_close(p->done) != 0)
		return (1);
/*  	if (sem_close(p->philo->eating) != 0)
	{
		printf("eat faillll\n");
		return (1);
	} */
	return (0);
}

/* void	ft_leaks(void)
{
	system("leaks -q philo_bonus");
} */

void	ft_free(t_main *p)
{
	free(p->philo);
	free(p->pid);
	free(p);
}

int	main(int argc, char **argv)
{
	t_main	*p;
	int		status;

	if (argv_check(argv) == 1 || argc < 5 || argc > 7)
		return (usage());
	p = malloc(sizeof(t_main));
	if (p == NULL)
		return (err("error: fatal\n"));
	if (init(argv, p) == 1)
	{
		free(p);
		return (1);
	}
	create_philos(p);
	int	i = 0;
	while (i < p->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status)
		{
			i = -1;
			i = -1;
			while(++i < p->num_philos)
				sem_close(&(p->philo->eating[i]));
			while(++i < p->num_philos)
				kill(p->pid[i], SIGTERM);
		}
		i++;
	}
	//atexit(ft_leaks);
	close_semaphores(p);
	ft_free(p);
	return (0);
}
