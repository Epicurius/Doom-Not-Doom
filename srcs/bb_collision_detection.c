/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bb_collision_detection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/29 17:50:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//int		hitbox_collision2(t_v3 p, t_v3 v1, t_v3 v2, double radius)



static int	portal_hitbox(t_doom *doom, t_motion *motion, t_wall *wall)
{
	double	portal_top;
	double	portal_bot;

	t_v3 point = closest_point_on_segment_v2(motion->where, wall->v1, wall->v2);
	portal_bot = ft_max(get_floor_at_pos(&doom->sectors[motion->curr_sect], point), get_floor_at_pos(&doom->sectors[wall->n], point));
	portal_top = ft_min(get_ceiling_at_pos(&doom->sectors[motion->curr_sect], point), get_ceiling_at_pos(&doom->sectors[wall->n], point));
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
	portal_bot = ft_max(get_floor_at_pos(&doom->sectors[motion->curr_sect], point), get_floor_at_pos(&doom->sectors[wall->n], point));
	portal_top = ft_min(get_ceiling_at_pos(&doom->sectors[motion->curr_sect], point), get_ceiling_at_pos(&doom->sectors[wall->n], point));
	if (portal_top <= portal_bot + motion->height)
		return (0);
	if (portal_top > motion->where.z + motion->height && portal_bot <= motion->where.z + STEP_HEIGHT)
	{
		print_v3("POINT:\t", point);
		motion->move = add_v3(motion->move, sub_v3(point, motion->where));
		//point.z = get_floor_at_pos(&doom->sectors[wall->n], point);
		//motion->where.z = get_floor_at_pos(&doom->sectors[wall->n], point);
		motion->where = point;
		motion->velocity = sub_v3(motion->future, motion->where);
		motion->prev_sect = motion->curr_sect;
		motion->curr_sect = wall->n;
		return (1);
	}
	return (0);
}

int	h_collision(t_doom *doom, t_motion *motion)
{
	int		i;
	t_wall	*wall;


	i = -1;
	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		wall = doom->sectors[motion->curr_sect].wall[i];
		if (wall->solid || wall->n == -1)
		{
			if (intersection_check(motion->where, motion->future, wall->v1, wall->v2))
				return (1);
			else if (hitbox_collision2(motion->future, wall->v1, wall->v2, 1.0))
				return (2);
		}
	}
	i = -1;
	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		wall = doom->sectors[motion->curr_sect].wall[i];
		if (!wall->solid && wall->n != -1 && wall->n != motion->prev_sect)
		{
			if (intersection_check(motion->where, motion->future, wall->v1, wall->v2))
			{
				if (portal_intersect(doom, motion, wall))
				{
					h_collision(doom, motion);
					return (3);
				}
			}
			if (hitbox_collision2(motion->future, wall->v1, wall->v2, 1.0))
			{
				if (!portal_hitbox(doom, motion, wall))
					return (4);
			}	
		}
	}
	//Maybe ccheck vcol before giving the ok?
	motion->move = add_v3(motion->move, motion->velocity);
	return (0);
}

int		check_floor1(t_doom *doom, t_motion *motion, int dest_set)
{
	double	floor;

	floor = get_floor_at_pos(&doom->sectors[dest_set], motion->future);
	if (floor > motion->future.z + 2 && dest_set != motion->sector)
		return (0);
	if ((doom->sectors[dest_set].floor_slope != 0
		&& floor > motion->future.z + 1 && dest_set == motion->sector && !motion->flight)
		|| (floor > motion->future.z && dest_set == motion->sector && motion->flight))
		return (0);
	return (1);
}

int	v_collision(t_doom *doom, t_motion *motion)
{
	t_fc		y;

	y.ceiling = get_ceiling_at_pos(&doom->sectors[motion->curr_sect], motion->where);
	y.floor = get_floor_at_pos(&doom->sectors[motion->curr_sect], motion->where);
	if (y.ceiling - y.floor < motion->height)
		return ((motion->suffocate = 1));
	if (!motion->flight && motion->where.z > y.floor)
	{
		ft_printf("[1] ");
		motion->velocity.z -= doom->sectors[motion->curr_sect].gravity;
		motion->where.z += motion->velocity.z;
	}
		
	if (motion->where.z < y.floor || motion->where.z + motion->velocity.z < y.floor)
	{
		ft_printf("[2] ");
		motion->velocity.z = 0;
		motion->where.z = y.floor;
	}
	if (motion->velocity.z >= 0 && motion->future.z + 1 > y.ceiling)
	{
		ft_printf("[3] ");
		if (motion->velocity.z > 0)
			motion->velocity.z = -doom->sectors[motion->curr_sect].gravity;
		//motion->where.z = y.ceiling - motion->height;
	}
	return (0);
}

t_v3	bb_collision_detection(t_doom *doom, t_v3 velocity, t_motion motion)
{
	t_v3 move;
	
	motion.velocity = doom->player.velocity;
	motion.curr_sect = doom->player.sector;
	motion.prev_sect = doom->player.sector;
	motion.future = add_v3(motion.where, velocity);
	motion.move = new_v3(0, 0, 0);
	if (v_collision(doom, &motion))
		return (move);
	motion.future = add_v3(motion.where, velocity);

	print_v3("VELOCITY:\t", motion.velocity);
	int i = h_collision(doom, &motion);
	if(i)
		motion.move.z += motion.velocity.z;
	doom->player.sector = motion.curr_sect;
	ft_printf("%d\t%d", motion.curr_sect, i);
	move = motion.move;
	print_v3("MOVE:\t", move);
	print_v3("POS:\t", add_v3(doom->player.where, move));
	//doom->player.sector = motion->curr_sect;
	//doom->player.sector = find_sector(doom->sectors, doom->nb.sectors, add_v3(doom->player.where, move));
	return (move);
}
