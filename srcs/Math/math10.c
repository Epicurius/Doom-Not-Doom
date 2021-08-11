/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math10.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 10:04:14 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/11 13:08:26 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

/*
 *	Print t_v2 components.
 */
void	print_v2(char *str, t_v2 v)
{
	if (str)
		ft_printf("%s\t", str);
	ft_printf("[%.2f\t%.2f]\n", v.x, v.y);
}

/*
 *	Print t_v3 components.
 */
void	print_v3(char *str, t_v3 v)
{
	if (str)
		ft_printf("%s\t", str);
	ft_printf("[%.2f\t%.2f\t%.2f]\n", v.x, v.y, v.z);
}
