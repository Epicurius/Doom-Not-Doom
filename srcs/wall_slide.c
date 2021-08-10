/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_slide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 10:59:44 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/10 09:57:11 by nneronin         ###   ########.fr       */
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

int	slide_check_solid_walls(t_doom *doom, t_motion *motion, int sect)
{
	int		i;
	t_wall	*wall;
	t_v3	point;
	double	ptop;
	double	pbot;

	i = -1;
	while (++i < doom->sectors[sect].npoints)
	{
		wall = doom->sectors[sect].wall[i];
		point = closest_point_on_segment_v2(motion->dest, wall->v1, wall->v2);
		if (intersect_v2(motion->where, motion->dest, wall->v1, wall->v2)
			|| (point_distance_v2(point.x, point.y, motion->dest.x, motion->dest.y) <= DIAMETER))
		{
			if (wall->solid || wall->n == -1)
				return (1);
			pbot = ft_max(
					floor_at(&doom->sectors[sect], point),
					floor_at(&doom->sectors[wall->n], point));
			ptop = ft_min(
					ceiling_at(&doom->sectors[sect], point),
					ceiling_at(&doom->sectors[wall->n], point));
			if (ptop <= pbot + motion->height)
				return (1);
			if (ptop <= motion->dest.z + motion->height || pbot > motion->dest.z + STEP_HEIGHT)
				return (1);
			if (doom->sectbool[wall->n] == FALSE)
			{
				doom->sectbool[wall->n] = TRUE;
				if (check_solid_surfaces(doom, motion, wall->n))
					return (1);
			}
		}
	}
	return (0);
}

int	slide_collision(t_doom *doom, t_motion *motion, t_wall *wall)
{
	t_motion	new;
	
	new = *motion;
	new.velocity = parallel_movement(motion->velocity, wall->v1, wall->v2);
	new.dest = add_v3(new.where, new.velocity);
	if (!slide_check_solid_walls(doom, &new, new.curr_sect))
	{
		motion->velocity.x = new.velocity.x;
		motion->velocity.y = new.velocity.y;
		return (0);
	}
	return (1);
}
