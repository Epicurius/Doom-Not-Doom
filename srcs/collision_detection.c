/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/30 12:17:28 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		hitbox_collision2(t_v3 p, t_v3 v1, t_v3 v2, double radius)
{
	double	len;
	double	dot;
	t_v3	closest;

	if (point_distance_v2(v1.x, v1.y, p.x, p.y) <= radius ||
		point_distance_v2(v2.x, v2.y, p.x, p.y) <= radius)
		return (1);
	len = point_distance_v2(v1.x, v1.y, v2.x, v2.y);
	dot = (((p.x - v1.x) * (v2.x - v1.x))
		+ ((p.y - v1.y) * (v2.y - v1.y))) / (len * len);
	closest.x = v1.x + (dot * (v2.x - v1.x));
	closest.y = v1.y + (dot * (v2.y - v1.y));
	if (!point_on_segment_v2(closest, v1, v2, 0.1))
		return (0);
	if (point_distance_v2(closest.x, closest.y, p.x, p.y) <= radius)
		return (1);
	return (0);
}

int		hitbox_collision(t_v3 p, t_v3 v1, t_v3 v2, double radius)
{
	t_v3	point;

	point = closest_point_on_segment_v2(p, v1, v2);
	int my = (point_distance_v2(point.x, point.y, p.x, p.y) <= radius);
	int his = hitbox_collision2(p, v1, v2, radius);
	if (my != his)
		ft_printf("{Contact Niklas!!!!!} %d %d\n", my, his);
	return (his);
}

static int	portal_hitbox(t_doom *doom, t_motion *motion, t_wall *wall)
{
	double	portal_top;
	double	portal_bot;

	t_v3 point = closest_point_on_segment_v2(motion->where, wall->v1, wall->v2);
	portal_bot = ft_max(floor_at(&doom->sectors[motion->curr_sect], point), floor_at(&doom->sectors[wall->n], point));
	portal_top = ft_min(ceiling_at(&doom->sectors[motion->curr_sect], point), ceiling_at(&doom->sectors[wall->n], point));
	if (portal_top <= portal_bot + motion->height)
		return (0);
	if (portal_top > motion->where.z + motion->height && portal_bot <= motion->where.z + STEP_HEIGHT)
	{
		return (1);
	}
	return (0);
}

static int	portal_intersect(t_doom *doom, t_motion *motion, t_wall *wall)
{
	double	portal_top;
	double	portal_bot;

	t_v3 point = closest_point_on_segment_v2(motion->where, wall->v1, wall->v2);
	portal_bot = ft_max(floor_at(&doom->sectors[motion->curr_sect], point), floor_at(&doom->sectors[wall->n], point));
	portal_top = ft_min(ceiling_at(&doom->sectors[motion->curr_sect], point), ceiling_at(&doom->sectors[wall->n], point));
	if (portal_top <= portal_bot + motion->height)
		return (0);
	if (portal_top > motion->where.z + motion->height && portal_bot <= motion->where.z + STEP_HEIGHT)
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

int	horizontal_collision(t_doom *doom, t_motion *motion)
{
	int		i;
	t_wall	*wall;

	i = -1;
	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		wall = doom->sectors[motion->curr_sect].wall[i];
		if (wall->solid || wall->n == -1)
		{
			if (intersect_check_v2(motion->where, motion->future, wall->v1, wall->v2))
			{
				slide_collision(doom, motion, wall);
				return (1);	
			}
			else if (hitbox_collision(motion->future, wall->v1, wall->v2, 1.0))
			{
				slide_collision(doom, motion, wall);
				return (2);
			}
		}
	}
	i = -1;
	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		wall = doom->sectors[motion->curr_sect].wall[i];
		if (!wall->solid && wall->n != -1 && wall->n != motion->prev_sect)
		{
			if (intersect_check_v2(motion->where, motion->future, wall->v1, wall->v2))
			{
				if (portal_intersect(doom, motion, wall))
				{
					horizontal_collision(doom, motion);
					return (-1);
				}
			}
			if (hitbox_collision(motion->future, wall->v1, wall->v2, 1.0))
			{
				if (!portal_hitbox(doom, motion, wall))
				{
					slide_collision(doom, motion, wall);
					return (3);
				}
			}	
		}
	}
	motion->move.x += motion->velocity.x;
	motion->move.y += motion->velocity.y;
	return (0);
}

int	vertical_collision(t_doom *doom, t_motion *motion)
{
	t_fc		y;

	y.ceiling = ceiling_at(&doom->sectors[motion->curr_sect], motion->where);
	y.floor = floor_at(&doom->sectors[motion->curr_sect], motion->where);
	if (y.ceiling - y.floor < motion->height)
		return (1);

	int i = -1;
	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		t_wall *wall = doom->sectors[motion->curr_sect].wall[i];
		if (!wall->solid && wall->n != -1)
		{
			t_v3 point = closest_point_on_segment_v2(motion->where, wall->v1, wall->v2);
			int my = (point_distance_v2(point.x, point.y, motion->where.x, motion->where.y) <= 1.0);
			if (my && motion->where.z <= floor_at(&doom->sectors[wall->n], point))
			{
				if (motion->velocity.z < 0)
					motion->velocity.z = 0;
				break ;
			}
		}
	}

	if (i >= doom->sectors[motion->curr_sect].npoints && !motion->flight && motion->where.z > y.floor)
	{
		motion->velocity.z -= doom->sectors[motion->curr_sect].gravity;
		motion->where.z += motion->velocity.z;
	}	
	if (motion->where.z < y.floor || motion->where.z + motion->velocity.z < y.floor)
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


int	collision_detection(t_doom *doom, t_motion motion, t_v3 *where, t_v3 *velocity)
{
	motion.where = *where;
	motion.velocity = *velocity;
	motion.prev_sect = motion.curr_sect;
	motion.move = new_v3(0.0f, 0.0f, 0.0f);
	if (vertical_collision(doom, &motion))
		return (-1);
	motion.future = add_v3(motion.where, motion.velocity);
	horizontal_collision(doom, &motion);
	*velocity = motion.move;
	*where = add_v3(*where, *velocity);
	if (where->z < floor_at(&doom->sectors[motion.curr_sect], *where))
	{
		velocity->z = 0;
		where->z = floor_at(&doom->sectors[motion.curr_sect], *where);
	}
	if (!in_sector(&doom->sectors[motion.curr_sect], *where))
	{
		ft_printf("{RED}[ERROR]{RESET}\tWrong Sector\n");
		motion.curr_sect = find_sector(doom->sectors, doom->nb.sectors, *where);
	}
	return (motion.curr_sect);
}


