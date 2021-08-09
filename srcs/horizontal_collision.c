/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_collision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:32:22 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/07 09:25:40y nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	portal_intersect(t_doom *doom, t_motion *motion, t_wall *wall)
{
	t_v3	point;

	doom->sectbool[wall->n] = TRUE;
	//point = closest_point_on_segment_v2(motion->where, wall->v1, wall->v2);
	//motion->move.x += point.x - motion->where.x;
	//motion->move.y += point.y - motion->where.y;
	//motion->where.x = point.x;
	//motion->where.y = point.y;
	//motion->velocity.x = motion->future.x - motion->where.x;
	//motion->velocity.y = motion->future.y - motion->where.y;
	motion->curr_sect = wall->n;
}

static int	horizontal_collision_portal(t_doom *doom, t_motion *motion, t_wall *wall)
{
	if (!wall->solid && wall->n != -1 && doom->sectbool[wall->n] != TRUE)
	{
		if (intersect_v2(motion->where, motion->future, wall->v1, wall->v2))
		{
			portal_intersect(doom, motion, wall);
			horizontal_collision(doom, motion);
			return (motion->type = -1);
		}
	}
	return (0);
}

int	horizontal_collision(t_doom *doom, t_motion *motion)
{
	int		i;
	t_wall	*wall;

	i = -1;
	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		wall = doom->sectors[motion->curr_sect].wall[i];
		horizontal_collision_portal(doom, motion, wall);
		//if (horizontal_collision_portal(doom, motion, wall))
		//	return (motion->type);
	}
	motion->move.x += motion->velocity.x;
	motion->move.y += motion->velocity.y;
	motion->type = 0;
	return (0);
}
