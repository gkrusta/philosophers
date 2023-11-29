/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:55:04 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/29 12:36:03 by gkrusta          ###   ########.fr       */
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

struct s_main;

typedef struct		s_philo {
	int				id;
	int				nb_eat;
	long long		last_meal;
	int				left_f;
	int				right_f;
	struct s_main	*rule;
	pthread_t		p_id;
}					t_philo;

typedef struct		s_main {
	int				num_philos;
	int				dead_flag;
	int				done_eating;
	t_philo			philo[200];
	long long		start_t;
	int				life_t;
	int				eat_t;
	int				sleep_t;
	int				meals;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	nb_eat;
	pthread_mutex_t	eating;
	pthread_mutex_t	done;
}					t_main;

/* thread management */
int		control_threads(t_main *p);
int		destroy_mutex(t_main *p);

/* death checker */
void	time_over(t_main *p, t_philo *philo);
void	death_check(t_main *p, t_philo *philo);

/* routine */
void	*routine(void *void_p);
void	*eating(t_philo *p);
void	eat_one(t_philo *p);
void	action(t_philo *p, char *str);

/* initiliaze philosophers */
int		init(char **argv, t_main *p);
int		create_philos(t_main *p);
void	fill_philo_struct(t_main *p, int i, int j);
int		create_mutex(t_main *p);

/* utils */
void		usage();
int			argv_check(char **argv);
int			ft_atoi(const char	*str);
long long	get_time(void);
void		ft_usleep(long long int time);

#endif