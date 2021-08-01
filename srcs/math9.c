/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math9.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 13:41:44 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 13:42:11 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

//	clamp radians between degrees 0 -> 360
void	clamp_radians(double *angle)
{
	*angle *= CONVERT_TO_DEGREES;
	while (*angle > 360)
		*angle -= 360;
	while (*angle < 0)
		*angle += 360;
	*angle *= CONVERT_TO_RADIANS;
}

//	clamp degrees between 0 -> 360
void	clamp_degrees(double *angle)
{
	while (*angle > 360)
		*angle -= 360;
	while (*angle < 0)
		*angle += 360;
}

