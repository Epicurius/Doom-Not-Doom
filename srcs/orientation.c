/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:02 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/08 10:53:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	degree_fix(double *degrees)
{
	while (*degrees > 360)
		*degrees -= 360;
	while (*degrees <= 0)
		*degrees += 360;
}

int	orientation(t_xyz p1, t_xyz p2, double yaw, int nb_angles)
{
	double angle;
	double a;
	int i;

	if (nb_angles <= 1)
		return (0);	
	angle = (int)((atan2(p1.y - p2.y, p1.x - p2.x))
			* CONVERT_DEGREES) % 360;
	a = 360 / nb_angles;
	yaw -= a / 2;
	degree_fix(&yaw);
	degree_fix(&angle);
	i = 0;
	while (!(angle >= yaw + i * a && angle < yaw + (i + 1) * a))
	{
		if (angle < yaw - i * a && angle >= yaw - (i + 1) * a)
			return (nb_angles - 1 - i);
		i++;
	}
	return (i);
}
