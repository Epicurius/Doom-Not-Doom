/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_slide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 10:59:44 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/09 11:51:47 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static t_v3	parallel_movement(t_v3 m, t_v3 v1, t_v3 v2)
{
	double	move_norm;
	double	wall_norm;
	double	scl;
	t_v2	w;

	w.x = v2.x - v1.x;
	w.y = v2.y - v1.y;
	move_norm = pythagoras(m.x, m.y);
	wall_norm = pythagoras(w.x, w.y);
	scl = (w.x / wall_norm * m.x / move_norm)
		+ (w.y / wall_norm * m.y / move_norm);
	if (scl != 0)
	{
		m.x = move_norm * w.x / wall_norm * scl;
		m.y = move_norm * w.y / wall_norm * scl;
	}
	else
		return (new_v3(0, 0, 0));
	return (m);
}

static int	horizontal_slide_collision1(t_doom *doom, t_motion *motion)
{
	int		i;
	t_wall	*wall;
	int	intersect;
	int	collision;

	i = -1;
	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		intersect = FALSE;
		collision = FALSE;
		wall = doom->sectors[motion->curr_sect].wall[i];
		if (intersect_v2(motion->where, motion->future, wall->v1, wall->v2))
			intersect = TRUE;
		else if (hitbox_collision(motion->future, wall->v1, wall->v2, DIAMETER))
			collision = TRUE;
		if ((wall->solid || wall->n == -1) && (intersect || collision))
			return (1);
		if ((!wall->solid && wall->n != -1) && (intersect || collision))
			return (3);
	}
	motion->move.x += motion->velocity.x;
	motion->move.y += motion->velocity.y;
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
		doom->sectbool[motion->curr_sect] == TRUE;
		motion->curr_sect = wall->n;
		return (1);
	}
	return (0);
}

static int	portal_hitbox(t_doom *doom, t_motion *motion, t_wall *wall)
{
	t_v3	point;
	double	portal_top;
	double	portal_bot;

	point = closest_point_on_segment_v2(motion->where, wall->v1, wall->v2);
	portal_bot = ft_max(
			floor_at(&doom->sectors[motion->curr_sect], point),
			floor_at(&doom->sectors[wall->n], point));
	portal_top = ft_min(
			ceiling_at(&doom->sectors[motion->curr_sect], point),
			ceiling_at(&doom->sectors[wall->n], point));
	if (portal_top <= portal_bot + motion->height)
		return (1);
	if (portal_top > motion->where.z + motion->height
		&& portal_bot <= motion->where.z + STEP_HEIGHT)
		return (0);
	return (1);
}

static int	horizontal_slide_collision(t_doom *doom, t_motion *motion)
{
	int		i;
	t_wall	*wall;
	int	intersect;
	int	collision;

	i = -1;
	while (++i < doom->sectors[motion->curr_sect].npoints)
	{
		intersect = FALSE;
		collision = FALSE;
		wall = doom->sectors[motion->curr_sect].wall[i];
		if (intersect_v2(motion->where, motion->future, wall->v1, wall->v2))
			intersect = TRUE;
		else if (hitbox_collision(motion->future, wall->v1, wall->v2, DIAMETER))
			collision = TRUE;
		if ((wall->solid || wall->n == -1) && (intersect || collision))
			return (1);
		if (!wall->solid && wall->n != -1 && doom->sectbool[wall->n] != TRUE)
		{
			//if (wall->v1.z == 1.0f && point_distance_v2(motion->future.x,
			//	motion->future.y, wall->v1.x, wall->v1.y) <= DIAMETER)
			//	return (3);
			//if (wall->v2.z == 1.0f && point_distance_v2(motion->future.x,
			//	motion->future.y, wall->v2.x, wall->v2.y) <= DIAMETER)
			//	return (4);
			if (intersect)
			{
				if (!portal_intersect(doom, motion, wall))
					return (2);
				horizontal_slide_collision(doom, motion);
				return (0);
			}
			else if (collision)
				if (portal_hitbox(doom, motion, wall))
					return (4);
		}
	}
	motion->move.x += motion->velocity.x;
	motion->move.y += motion->velocity.y;
	return (0);
}

void	slide_collision(t_doom *doom, t_motion *motion, t_wall *wall, int slide)
{
	t_motion	new;
	
	//ft_printf("asdasdasdasdasd %d\n", rand());
	if (slide == TRUE)
	{
		new = *motion;
		new.velocity = parallel_movement(motion->velocity, wall->v1, wall->v2);
		new.future = add_v3(new.where, new.velocity);
		int asd = horizontal_slide_collision1(doom, &new);
		//ft_printf("%d\n", asd);
		if (!asd)
		{
			motion->move = new.move;
			motion->velocity = new.velocity;
		}
	}
	//else
	//	ft_printf("Not\n");
	//else if (slide == FALSE)
	//	ft_bzero(&motion->move, sizeof(t_v3));
}
