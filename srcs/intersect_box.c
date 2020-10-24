/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_box.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 12:44:46 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/21 14:35:25 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// Determine whether the two number ranges overlap.
int		overlap(double a0, double a1, double b0, double b1)
{
	if (min(a0, a1) <= max(b0, b1) &&
		min(b0, b1) <= max(a0, a1))
		return (1);
	return (0);
}

// Determine whether two 2D-boxes intersect.
int		intersect_box(t_xyz p, t_xyz d, t_xyz vert1, t_xyz vert2)
{
	if (overlap(p.x, (p.x + d.x), vert1.x, vert2.x) &&
		overlap(p.y, (p.y + d.y), vert1.y, vert2.y))
		return (1);
	return (0);
}

// Determine which side of a line the point is on. Return value: <0, =0 or >0.
float	point_side(t_xyz p, t_xyz d, t_xyz vert1, t_xyz vert2)
{
	return (vxs(vert2.x - vert1.x,
				vert2.y - vert1.y,
				(p.x + d.x) - vert1.x,
				(p.y + d.y) - vert1.y));
}

