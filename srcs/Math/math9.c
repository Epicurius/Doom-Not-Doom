/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math9.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 13:41:44 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/19 17:30:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

/*
 *	Clamp radians between degrees 0 -> 360.
 */
void	clamp_radians(TEMP_DOUBLE *angle)
{
	*angle *= CONVERT_TO_DEGREES;
	while (*angle > 360)
		*angle -= 360;
	while (*angle < 0)
		*angle += 360;
	*angle *= CONVERT_TO_RADIANS;
}

/*
 *	Clamp degrees between 0 -> 360.
 */
void	clamp_degrees(TEMP_DOUBLE *angle)
{
	while (*angle > 360)
		*angle -= 360;
	while (*angle < 0)
		*angle += 360;
}
