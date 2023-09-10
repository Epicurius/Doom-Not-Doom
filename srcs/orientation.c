/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Returns the frame to be rendered,
 *	depending on the angle of the entity to the player.
 */
int	orientation(t_v3 p1, t_v3 p2, double yaw, int nb_angles)
{
	int		i;
	double	a;
	double	angle;

	if (nb_angles <= 1)
		return (0);
	yaw = (int)(yaw * CONVERT_TO_DEGREES) % 360;
	angle = (int)((atan2(p1.y - p2.y, p1.x - p2.x)) * CONVERT_TO_DEGREES) % 360;
	a = 360 / nb_angles;
	yaw -= a / 2;
	clamp_degrees(&yaw);
	clamp_degrees(&angle);
	i = 0;
	while (!(angle >= yaw + i * a && angle < yaw + (i + 1) * a))
	{
		if (angle < yaw - i * a && angle >= yaw - (i + 1) * a)
			return (nb_angles - 1 - i);
		i++;
	}
	return (i);
}
