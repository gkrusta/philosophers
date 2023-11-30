/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:53:50 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/30 18:07:48 by gkrusta          ###   ########.fr       */
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
	if (sem_close(p->nb_eat) != 0)
		return (1);
	if (sem_close(p->eating) != 0)
		return (1);
	if (sem_close(p->done) != 0)
		return (1);
	return (0);
}

/* void	ft_leaks(void)
{
	system("leaks -q philo");
} */

int	main(int argc, char **argv)
{
	t_main	*p;
	
	//atexit(ft_leaks);
	if (argv_check(argv) == 1 || argc < 5 || argc > 7)
	{
		usage();
		return (1);
	}
	p = malloc(sizeof(t_main));
	if (p == NULL)
		return (1);
	if (init(argv, p) == 1)
	{
		free(p);
		return (1);
	}
	int	i = 0;
	create_philos(p);
	waitpid(p->pid[i], NULL, 0);
	close_semaphores(p);
	free(p);
	return (0);
}