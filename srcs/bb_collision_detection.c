/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bb_collision_detection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/30 10:32:07 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_v3	parallel_movement(t_doom *doom, t_v3 velocity, t_wall *wall)
{
	double	norm_velo;
	double	norm_wall;
	double	scalar;
	t_v2	w;

	w.x = wall->v2.x - wall->v1.x;
	w.y = wall->v2.y - wall->v1.y;
	norm_velo = pythagoras(velocity.x, velocity.y);
	norm_wall = pythagoras(w.x, w.y);
	scalar = w.x / norm_wall * velocity.x / norm_velo +
		w.y / norm_wall * velocity.y / norm_velo;
	if (scalar != 0)
	{
		velocity.x = norm_velo * w.x / norm_wall * scalar;
		velocity.y = norm_velo * w.y / norm_wall * scalar;
	}
	else
		return (new_v3(0, 0, 0));
	return (velocity);
}

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
			if (intersect_check_v2(motion->where, motion->future, wall->v1, wall->v2))
			{
				//motion->velocity = parallel_movement(doom, motion->velocity, wall);
				//if (!h_collision(doom, motion))
				//	motion->move = motion->velocity;
				return (1);	
			}
			else if (hitbox_collision2(motion->future, wall->v1, wall->v2, 1.0))
			{
				//motion->velocity = parallel_movement(doom, motion->velocity, wall);
				//if (!h_collision(doom, motion))
				//	motion->move = motion->velocity;
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
	motion->move.x += motion->velocity.x;
	motion->move.y += motion->velocity.y;
	return (0);
}

int	v_collision(t_doom *doom, t_motion *motion)
{
	t_fc		y;

	y.ceiling = get_ceiling_at_pos(&doom->sectors[motion->curr_sect], motion->where);
	y.floor = get_floor_at_pos(&doom->sectors[motion->curr_sect], motion->where);
	if (y.ceiling - y.floor < motion->height)
		return (1);
	if (!motion->flight && motion->where.z > y.floor)
	{
		//ft_printf("[1] ");
		motion->velocity.z -= doom->sectors[motion->curr_sect].gravity;
		motion->where.z += motion->velocity.z;
	}	
	if (motion->where.z < y.floor || motion->where.z + motion->velocity.z < y.floor)
	{
		//ft_printf("[2] ");
		motion->velocity.z = 0;
		if (motion->where.z < y.floor)
			motion->where.z = y.floor;
	}
	if (motion->velocity.z > 0 && motion->where.z + motion->velocity.z + motion->height >= y.ceiling)
	{
		//ft_printf("[3] ");
		motion->velocity.z = 0;//-doom->sectors[motion->curr_sect].gravity;
		//motion->where.z += motion->velocity.z;
	}
	motion->move.z += motion->velocity.z;
	return (0);
}

int	bb_collision_detection(t_doom *doom, t_motion motion, t_v3 *where, t_v3 *velocity)
{
	motion.where = *where;
	motion.velocity = *velocity;
	motion.prev_sect = motion.curr_sect;
	motion.move = new_v3(0.0f, 0.0f, 0.0f);
	if (v_collision(doom, &motion))
		return (-1);
	motion.future = add_v3(motion.where, motion.velocity);
	//print_v3("VELOCITY:\t", motion.velocity);
	h_collision(doom, &motion);
	*velocity = motion.move;
	*where = add_v3(*where, *velocity);
	if (where->z < get_floor_at_pos(&doom->sectors[motion.curr_sect], *where))
	{
		velocity->z = 0;
		where->z = get_floor_at_pos(&doom->sectors[motion.curr_sect], *where);
	}
	//ft_printf("%d\t", doom->player.sector);
	//print_v3("MOVE:\t", motion.move);
	//print_v3("POS:\t",doom->player.where);
	if (!in_sector(&doom->sectors[motion.curr_sect], *where))
	{
		ft_printf("{RED}[ERROR]{RESET}\tWrong Sector\n");
		motion.curr_sect = find_sector(doom->sectors, doom->nb.sectors, *where);
	}
	return (motion.curr_sect);
}
