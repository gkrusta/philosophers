/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:53:34 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/25 16:40:32 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usage(void)
{
	printf("-----------------\n");
	printf("How to use:\n");
	printf("./philo number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep [number_of_meals]\n");
	printf("number of philosophers: 1-200\n");
	printf("the rest of the parametrs has to be > 0 which will be representing miliseconds\n");
	printf("-----------------\n");
}

int	argv_check(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			while (argv[i][j] == ' ')
				j++;
			while (argv[i][j] >= '0' && argv[i][j] <= '9')
			{
				if (argv[i][j] <= '0' || argv[i][j] >= '9')
					return (1);
				j++;
			}
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char	*str)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign *(-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (str[i] - '0') + (number * 10);
		i++;
	}
	return (sign * number);
}
