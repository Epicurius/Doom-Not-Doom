/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:52:17 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/10 13:01:36 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	portal_cliff(t_doom *doom, t_motion *motion, t_v3 where, int i)
{
	t_v3	point;
	t_wall	*wall;

	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		wall = doom->sectors[motion->curr_sect].wall[i];
		if (wall->solid || wall->n == -1)
			continue ;
		point = closest_point_on_segment_v2(where, wall->v1, wall->v2);
		if (point_distance_v2(point.x, point.y, where.x, where.y) > DIAMETER)
			continue ;
		if (where.z + motion->velocity.z
			<= floor_at(&doom->sectors[wall->n], point))
		{
			if (motion->velocity.z < 0)
				motion->velocity.z = 0;
			return (1);
		}
		if (where.z + motion->height + motion->velocity.z
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
	t_fc	pos;

	pos.ceiling = ceiling_at(&doom->sectors[motion->curr_sect], motion->where);
	pos.floor = floor_at(&doom->sectors[motion->curr_sect], motion->where);
	if (pos.ceiling - pos.floor < motion->height)
		return (1);
	if (motion->flight == FALSE && motion->where.z > pos.floor
		&& !portal_cliff(doom, motion, motion->where, -1))
	{
		motion->velocity.z -= doom->sectors[motion->curr_sect].gravity;
		motion->where.z += motion->velocity.z;
	}
	if (motion->where.z + motion->velocity.z + motion->height >= pos.ceiling)
		motion->velocity.z = 0;
	motion->move.z += motion->velocity.z;
	return (0);
}
