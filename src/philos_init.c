/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:23:12 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/25 15:21:00 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_p *p)
{
	int	i;
	int	j;

	p->philo = malloc(sizeof(t_philo) * (p->num_philos + 1));
	if (p->philo == NULL)
		return (1);
	i = 0;
	j = 1;
	while (j < p->num_philos)
	{
		fill_philo_struct(p, i, j);
		i++;
		j++;
	}
	j = 0;
	fill_philo_struct(p, i, j);
	return (0);
}
void	fill_philo_struct(t_p *p, int i, int j)
{
	p->philo[i].id = i + 1;
	p->philo[i].nb_eat = 0;
	p->philo[i].life_t = 0;
	p->philo[i].left_f = i;
	p->philo[i].right_f = j;
	p->philo[i].
}