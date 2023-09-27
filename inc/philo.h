/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:55:04 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/27 13:17:42 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
//#include <semaphore.h>

struct s_main;

typedef struct		s_philo {
	int				id;
	int				nb_eat;
	int				last_meal;
	int				left_f;
	int				right_f;
	struct s_main	*rule;
	pthread_t		p_id;
}					t_philo;

typedef struct		s_main {
	int				num_philos;
	int				dead_flag;
	u_int64_t		start_t;
	t_philo			philo[200];
	int				life_t;
	int				eat_t;
	int				sleep_t;
	int				meals;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	write;
	pthread_mutex_t	eating;
}					t_main;

/* initiliaze philosophers */
int		init(char **argv, t_main *p);
int		create_philos(t_main *p);
void	fill_philo_struct(t_main *p, int i, int j);
int		create_mutex(t_main *p);

/* utils */
void	usage(void);
int		argv_check(char **argv);
int		ft_atoi(const char	*str);
u_int64_t	get_time(void);

#endif