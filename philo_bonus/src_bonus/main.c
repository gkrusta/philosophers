/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:53:50 by gkrusta           #+#    #+#             */
/*   Updated: 2023/12/11 12:54:00 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	close_semaphores(t_main *p)
{
	if (sem_close(p->forks) != 0)
		return (1);
	if (sem_close(p->write) != 0)
		return (1);
	if (sem_close(p->done) != 0)
		return (1);
	if (sem_unlink("/forks") != 0)
		return (1);
	if (sem_unlink("/write") != 0)
		return (1);
	if (sem_unlink("/done") != 0)
		return (1);
	return (0);
}

void	ft_free(t_main *p)
{
	free(p->philo);
	free(p->pid);
	free(p);
}

int	main(int argc, char **argv)
{
	t_main	*p;

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
	terminate_processes(p);
	close_semaphores(p);
	ft_free(p);
	return (0);
}
