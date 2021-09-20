/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:38:37 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/20 10:27:48 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

/*
 *	x,y of vector
 */
void	get_polar_cooordinates(float len, float angle, t_v2 *polar)
{
	polar->x = len * cos(angle);
	polar->y = len * sin(angle);
}

/*
 *	len, angle of vector
 */
void	get_cartesian_cooordinates(float x, float y, float *len,
	float *angle)
{
	*len = sqrt(x * x + y * y);
	*angle = atan(y / x);
}

/*
 *	Deprecated, use #define RADIANS_CONVERT
 */
float	to_radians(float degrees)
{
	return (degrees * ((float)M_PI / 180.0f));
}

/*
 *	Deprecated, use #define DEGREES1_CONVERT
 */
float	to_degrees(float radians)
{
	return (radians * (180.0f / (float)M_PI));
}
