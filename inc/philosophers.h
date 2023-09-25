/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:55:04 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/25 15:20:52 by gkrusta          ###   ########.fr       */
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
	int			num_philos;
	int				philo_dead;
	long long		start_t;
	pthread_t		id;
	t_philo			philo[200];
	int				life_f;
	int				eat_t;
	int				sleep_t;
	int				meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*write;
}					t_main

typedef struct s_philo {
	int				id;
	int				nb_eat;
	int				left_f;
	int				right_f;
	struct t_main	*rule;
}					t_philo;

/* initiliaze philosophers */
int		create_philos(t_main *main);
void	fill_philo_struct(t_main *main, int i, int j);

/* utils */
void	usage(void);
int		argv_check(char **argv);
int		ft_atoi(const char	*str);

#endif