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

static int	portal_hitbox(t_doom *doom, t_motion *motion, t_wall *wall)
{
	t_v3	point;
	double	portal_top;
	double	portal_bot;

	point = closest_point_on_segment_v2(motion->where, wall->v1, wall->v2);
	portal_bot = ft_max(floor_at(&doom->sectors[motion->curr_sect], point),
			floor_at(&doom->sectors[wall->n], point));
	portal_top = ft_min(ceiling_at(&doom->sectors[motion->curr_sect], point),
			ceiling_at(&doom->sectors[wall->n], point));
	if (portal_top <= portal_bot + motion->height)
		return (1);
	if (portal_top > motion->where.z + motion->height
		&& portal_bot <= motion->where.z + STEP_HEIGHT)
	{
		//doom->sectbool[wall->n] == TRUE;
		return (0);
	}
	return (1);
}

static int	portal_intersect(t_doom *doom, t_motion *motion, t_wall *wall)
{
	t_v3	point;
	double	portal_top;
	double	portal_bot;

	point = closest_point_on_segment_v2(motion->where, wall->v1, wall->v2);
	portal_bot = ft_max(floor_at(&doom->sectors[motion->curr_sect], point),
			floor_at(&doom->sectors[wall->n], point));
	portal_top = ft_min(ceiling_at(&doom->sectors[motion->curr_sect], point),
			ceiling_at(&doom->sectors[wall->n], point));
	if (portal_top <= portal_bot + motion->height)
		return (0);
	if (portal_top > motion->where.z + motion->height
		&& portal_bot <= motion->where.z + STEP_HEIGHT)
	{
		motion->move.x += point.x - motion->where.x;
		motion->move.y += point.y - motion->where.y;
		motion->where.x = point.x;
		motion->where.y = point.y;
		motion->velocity.x = motion->future.x - motion->where.x;
		motion->velocity.y = motion->future.y - motion->where.y;
		doom->sectbool[motion->curr_sect] == TRUE;
		motion->curr_sect = wall->n;
		return (1);
	}
	return (0);
}

static int	horizontal_collision_wall(t_doom *doom,
	t_motion *motion, t_wall *wall, int slide)
{
	if (wall->solid || wall->n == -1)
	{
		if (intersect_v2(motion->where, motion->future, wall->v1, wall->v2))
		{
			slide_collision(doom, motion, wall, slide);
			return (motion->type = 1);
		}
		if (hitbox_collision(motion->future, wall->v1, wall->v2, DIAMETER))
		{
			slide_collision(doom, motion, wall, slide);
			return (motion->type = 2);
		}
	}
	else
	{
		if (wall->v1.z == 1.0f && point_distance_v2(motion->future.x,
			motion->future.y, wall->v1.x, wall->v1.y) <= DIAMETER)
			return (motion->type = 3);
		if (wall->v2.z == 1.0f && point_distance_v2(motion->future.x,
			motion->future.y, wall->v2.x, wall->v2.y) <= DIAMETER)
			return (motion->type = 4);
	}
	return (0);
}

static int	horizontal_collision_portal(t_doom *doom,
	t_motion *motion, t_wall *wall, int slide)
{
	if (!wall->solid && wall->n != -1 && doom->sectbool[wall->n] != TRUE)
	{
		if (intersect_v2(motion->where, motion->future, wall->v1, wall->v2))
		{
			if (portal_intersect(doom, motion, wall))
			{
				horizontal_collision(doom, motion, slide);
				return (motion->type = -1);
			}
		}
		if (hitbox_collision(motion->future, wall->v1, wall->v2, DIAMETER))
		{
			if (portal_hitbox(doom, motion, wall))
			{
				slide_collision(doom, motion, wall, slide);
				return (motion->type = 5);
			}
		}
	}
	return (0);
}

int	horizontal_collision(t_doom *doom, t_motion *motion, int slide)
{
	int		i;
	t_wall	*wall;

	i = -1;
	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		wall = doom->sectors[motion->curr_sect].wall[i];
		if (horizontal_collision_wall(doom, motion, wall, slide))
			return (motion->type);
	}
	i = -1;
	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		wall = doom->sectors[motion->curr_sect].wall[i];
		if (horizontal_collision_portal(doom, motion, wall, slide))
			return (motion->type);
	}
	motion->move.x += motion->velocity.x;
	motion->move.y += motion->velocity.y;
	motion->type = 0;
	return (0);
}
