/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_timer_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 16:05:25 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/03 13:27:44 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>

clock_t	g_clock_start;

void	ft_timer_start(void)
{
	g_clock_start = clock();
}

double	ft_timer_end(void)
{
	double	cpu_time_used;
	clock_t	end;

	end = clock();
	cpu_time_used = ((double)(end - g_clock_start)) / CLOCKS_PER_SEC;
	return (cpu_time_used);
}
