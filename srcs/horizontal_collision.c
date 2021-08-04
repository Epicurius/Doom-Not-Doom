/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_collision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:32:22 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/04 09:59:25 by nneronin         ###   ########.fr       */
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
		return (0);
	if (portal_top > motion->where.z + motion->height
		&& portal_bot <= motion->where.z + STEP_HEIGHT)
		return (1);
	return (0);
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
		motion->prev_sect = motion->curr_sect;
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
		if (intersect_check_v2(motion->where, motion->future,
				wall->v1, wall->v2))
		{
			slide_collision(doom, motion, wall, slide);
			motion->type = 1;
			return (1);
		}
		else if (hitbox_collision(motion->future, wall->v1, wall->v2, 1.0))
		{
			slide_collision(doom, motion, wall, slide);
			motion->type = 2;
			return (2);
		}
	}
	return (0);
}

static int	horizontal_collision_portal(t_doom *doom,
	t_motion *motion, t_wall *wall, int slide)
{
	if (!wall->solid && wall->n != -1 && wall->n != motion->prev_sect)
	{
		if (intersect_check_v2(motion->where, motion->future,
				wall->v1, wall->v2))
		{
			if (portal_intersect(doom, motion, wall))
			{
				horizontal_collision(doom, motion, slide);
				motion->type = -1;
				return (-1);
			}
		}
		if (hitbox_collision(motion->future, wall->v1, wall->v2, 1.0))
		{
			if (!portal_hitbox(doom, motion, wall))
			{
				slide_collision(doom, motion, wall, slide);
				motion->type = 3;
				return (3);
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
