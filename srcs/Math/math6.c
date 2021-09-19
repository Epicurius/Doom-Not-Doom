/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:38:37 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/19 17:30:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

/*
 *	x,y of vector
 */
void	get_polar_cooordinates(TEMP_DOUBLE len, TEMP_DOUBLE angle, t_v2 *polar)
{
	polar->x = len * cos(angle);
	polar->y = len * sin(angle);
}

/*
 *	len, angle of vector
 */
void	get_cartesian_cooordinates(TEMP_DOUBLE x, TEMP_DOUBLE y, TEMP_DOUBLE *len,
	TEMP_DOUBLE *angle)
{
	*len = sqrt(x * x + y * y);
	*angle = atan(y / x);
}

/*
 *	Deprecated, use #define RADIANS_CONVERT
 */
TEMP_DOUBLE	to_radians(TEMP_DOUBLE degrees)
{
	return (degrees * ((TEMP_DOUBLE)M_PI / 180.0f));
}

/*
 *	Deprecated, use #define DEGREES1_CONVERT
 */
TEMP_DOUBLE	to_degrees(TEMP_DOUBLE radians)
{
	return (radians * (180.0f / (TEMP_DOUBLE)M_PI));
}
