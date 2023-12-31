/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:53:50 by gkrusta           #+#    #+#             */
/*   Updated: 2023/12/10 16:00:14 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(t_main *p)
{
	int	i;

	i = 0;
	while (i < p->num_philos)
	{
		if (pthread_mutex_destroy(&(p->forks[i])) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(&(p->done)) != 0)
		return (1);
	if (pthread_mutex_destroy(&(p->eating)) != 0)
		return (1);
	return (0);
}

int	control_threads(t_main *p)
{
	int	i;

	i = 0;
	p->start_t = get_time();
	while (i < p->num_philos)
	{
		if (pthread_create(&(p->philo[i].p_id), NULL, routine, &(p->philo[i]))
			!= 0)
			return (1);
		i++;
	}
	death_check(p, p->philo);
	i = 0;
	while (i < p->num_philos)
	{
		if (pthread_join(p->philo[i].p_id, NULL) != 0)
			return (1);
		i++;
	}
	if (destroy_mutex(p) == 1)
		return (1);
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
	p = malloc(sizeof(t_main));
	if (p == NULL)
		return (1);
	if (init(argv, p) == 1)
	{
		free(p);
		return (1);
	}
	control_threads(p);
	free(p);
	return (0);
}
