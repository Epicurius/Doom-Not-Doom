/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:38:37 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/17 17:35:45 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

/*
 *	x,y of vector
 */
void	get_polar_cooordinates(TEMP_FLOAT len, TEMP_FLOAT angle, t_v2 *polar)
{
	polar->x = len * cos(angle);
	polar->y = len * sin(angle);
}

/*
 *	len, angle of vector
 */
void	get_cartesian_cooordinates(TEMP_FLOAT x, TEMP_FLOAT y, TEMP_FLOAT *len,
	TEMP_FLOAT *angle)
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
