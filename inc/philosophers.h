/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:55:04 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/24 18:36:49 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <sys/time.h>

struct t_philo

typedef struct s_main {
	int				philo_dead;
	long long		start_t;
	t_input			input;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
}				t_main

typedef struct s_philo {
	int		num_philos;
	pthread_t	id;
	int	philosophers;
	int	life_f;
	int	eat_t;
	int	sleep_t;
	int	meals;
	//int	think_t;
	int	left_f;
	int	right_f;
}		t_philo;

/* initiliaze philosophers */
int		create_philos(t_main *main);
void	fill_philo_struct(t_main *main, int i, int j);

/* utils */
void	usage(void);
int		argv_check(char **argv);
int		ft_atoi(const char	*str);

#endif