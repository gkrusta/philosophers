/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:40:47 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/24 18:35:22 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	*tp;
	
	gettimeofday(tp, NULL);
	return ((tp.tv_sec * (u_int64_t)1000) + (tp.tv_usec / 1000));
}

int	init(int argc, char **argv, t_philo *p)
{
	int	i;

	i = 1;
	p->philosophers = ft_atoi(argv[1]);
	p->life_t = ft_atoi(argv[2]);
	p->eat_t = ft_atoi(argv[3]);
	p->sleep_t = ft_atoi(argv[4]);
	if (argv[5])
		p->meals = ft_atoi(argv[5]);
	if (p->philosophers < 1 || p->life_t <= 0 || p->eat_t <= 0 || p->sleep_t <= 0)
	{
		free(p);
		usage();
		return(1);
	}
	while (i < argc)
	{
		
		i++;
	}
	return (0);
}

void	start(t_philo *p)
{
	pthread_mutex_t	mutex;
	
	pthread_mutex_init(&mutex, NULL);
}

int	main(int argc, char **argv)
{
	t_philo	*p;

	if (argv_check(argv) == 1 || argc < 5 || argc > 7)
	{
		usage();
		return (1);
	}
	if (init(argc, argv, p) == 1);
	{
		usage();
		return (1);
	}
	start(p);
	return (0);
}
