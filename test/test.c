/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:41:23 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/26 15:48:56 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
int main(void)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    printf("time is %ld \n", tp.tv_sec*100 + tp.tv_usec/100);
    return (0);
}