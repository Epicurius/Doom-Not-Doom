/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:38:47 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/19 17:30:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

/*
 *	Set p1 angle to p2 (DEGREES)
 */
TEMP_DOUBLE	angle_to_point_v2(t_v3 p1, t_v3 p2)
{
	TEMP_DOUBLE	angle;

	angle = atan2(p2.y - p1.y, p2.x - p1.x) * CONVERT_TO_DEGREES;
	clamp_degrees(&angle);
	return (angle);
}

/*
 *	Return sign
 */
int	ft_sign(TEMP_DOUBLE x)
{
	if (x > 0)
		return (1);
	if (x < 0)
		return (-1);
	return (0);
}

/*
 *	Determine which side of a line the point is on. Return value: <0, =0 or >0.
 */
TEMP_DOUBLE	point_side_v2(t_v3 v1, t_v3 v2, t_v3 p)
{
	return ((v2.x - v1.x) * (p.y - v1.y) - (v2.y - v1.y) * (p.x - v1.x));
}

/*
 *	Distance between 2 2d points
 */
TEMP_DOUBLE	point_distance_v2(TEMP_DOUBLE x1, TEMP_DOUBLE y1, TEMP_DOUBLE x2, TEMP_DOUBLE y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
