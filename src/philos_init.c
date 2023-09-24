/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:23:12 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/24 18:34:19 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_main *main)
{
	int	i;
	int	j;

	main->philo = malloc(sizeof(t_philo) * (main->num_philos + 1));
	if (main->philo == NULL)
		return (1);
	i = 0;
	j = 1;
	while (j < main->num_philos)
	{
		fill_philo_struct(main, i, j);
		i++;
		j++;
	}
	j = 0;
	fill_philo_struct(main, i, j);
	return (0);
}

void	fill_philo_struct(t_main *main, int i, int j)
{
	main->philo[i].id = i + 1;
	main->philo[i].meals = 0;
	main->philo[i].life_t = 0;
	main->philo[i].left_f = i;
	main->philo[i].right_f = j;
}