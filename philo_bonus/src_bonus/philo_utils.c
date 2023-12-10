/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:53:34 by gkrusta           #+#    #+#             */
/*   Updated: 2023/12/10 12:35:38 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	usage()
{
	printf("-----------------\n");
	printf("- How to use:\n");
	printf("./philo_bonus number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep [number_of_meals]\n");
	printf("number of philosophers: 1-200\n");
	printf("the rest of the parametrs has to be > 60 which will be representing miliseconds\n");
	printf("-----------------\n");
	return (1);
}

int	ft_numblen(long n)
{
	int	count;

	count = 1;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	long	nr;

	nr = n;
	if (nr < 0)
		nr *= (-1);
	len = ft_numblen(nr);
	if (n < 0)
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len--] = '\0';
	while (len >= 0)
	{
		result[len--] = nr % 10 + '0';
		nr /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}

int	argv_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
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
