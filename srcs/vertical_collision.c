/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:52:17 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/07 16:21:11 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	portal_cliff(t_doom *doom, t_motion *motion, t_v3 where)
{
	int		i;
	t_v3	point;
	double	dist;
	t_wall	*wall;

	i = -1;
	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		wall = doom->sectors[motion->curr_sect].wall[i];
		if (wall->solid || wall->n == -1)
			continue ;
		point = closest_point_on_segment_v2(where, wall->v1, wall->v2);
		dist = point_distance_v2(point.x, point.y, where.x, where.y);
		
		if (dist <= DIAMETER && where.z <= floor_at(&doom->sectors[wall->n], point))
		{
			if (motion->velocity.z < 0)
				motion->velocity.z = 0;
			return (1);
		}
		if (dist <= DIAMETER && where.z + motion->height + motion->velocity.z
			>= ceiling_at(&doom->sectors[wall->n], point))
		{
			motion->velocity.z = 0;
			return (1);
		}
	}
	return (0);
}

int	vertical_collision(t_doom *doom, t_motion *motion)
{
	t_fc	y;

	y.ceiling = ceiling_at(&doom->sectors[motion->curr_sect], motion->where);
	y.floor = floor_at(&doom->sectors[motion->curr_sect], motion->where);
	if (y.ceiling - y.floor < motion->height)
		return (1);
	if (!portal_cliff(doom, motion, motion->where) && !motion->flight && motion->where.z > y.floor)
	{
		motion->velocity.z -= doom->sectors[motion->curr_sect].gravity;
		motion->where.z += motion->velocity.z;
	}
	// if breaks enable this || motion->where.z + motion->velocity.z < y.floor)
	if (motion->where.z < y.floor)
	{
		motion->velocity.z = 0;
		if (motion->where.z < y.floor)
			motion->where.z = y.floor;
	}
	if (motion->velocity.z > 0 && motion->where.z + motion->velocity.z + motion->height >= y.ceiling)
		motion->velocity.z = 0;
	motion->move.z += motion->velocity.z;
	return (0);
}
