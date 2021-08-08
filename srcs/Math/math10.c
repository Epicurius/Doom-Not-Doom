/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math10.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 10:04:14 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/08 10:11:27 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

void	print_v2(char *str, t_v2 v)
{
	if (str)
		ft_printf("%s\t", str);
	ft_printf("[%.2f\t%.2f]\n", v.x, v.y);
}

void	print_v3(char *str, t_v3 v)
{
	if (str)
		ft_printf("%s\t", str);
	printf("[%f\t%f\t%f]\n", v.x, v.y, v.z);//ft_
}
