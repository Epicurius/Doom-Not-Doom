/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:02 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/20 11:28:46 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	i = 0;
	while (!(angle >= yaw + i * a && angle < yaw + (i + 1) * a))
	{
		if (angle < yaw - i * a && angle >= yaw - (i + 1) * a)
			return (nb_angles - 1 - i);
		i++;
	}
	return (i);
}
