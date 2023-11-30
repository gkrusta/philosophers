/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:55:04 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/30 17:46:20 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/cdefs.h>

struct s_main;

typedef struct		s_philo {
	int				id;
	int				nb_eat;
	long long		last_meal;
	int				left_f;
	int				right_f;
	struct s_main	*rule;
}					t_philo;

typedef struct		s_main {
	int				num_philos;
	bool			dead_flag;
	int				done_eating;
	pid_t			*pid;
	pthread_t		p_id;
	t_philo			*philo; // 1 pointer 
	long long		start_t;
	int				life_t;
	int				eat_t;
	int				sleep_t;
	int				meals;
	sem_t			*forks;
	sem_t			*nb_eat;
	sem_t			*eating;
	sem_t			*done;
}					t_main;

/* thread management */
int	close_semaphores(t_main *p);

/* death checker */
void	time_over(t_main *p, t_philo *philo);
void	*death_check(void *void_p);

/* routine */
void	routine(t_philo *p, t_main *philo);
void	eating(t_philo *p);
void	eat_one(t_philo *p);
void	action(t_philo *p, char *str);

/* initiliaze philosophers */
int		init(char **argv, t_main *p);
int		create_philos(t_main *p);
void	fill_philo_struct(t_main *p, int i, int j);

/* utils */
void		usage();
int			argv_check(char **argv);
int			ft_atoi(const char	*str);
long long	get_time(void);
void		ft_usleep(long long int time);

#endif