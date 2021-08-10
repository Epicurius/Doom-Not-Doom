/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_slide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 10:59:44 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/10 10:58:44 by nneronin         ###   ########.fr       */
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

int	check_solid_surfaces_no_slide(t_doom *doom, t_motion *motion, int sect)
{
	int		i;
	t_v3	point;
	t_wall	*wall;

	i = -1;
	while (++i < doom->sectors[sect].npoints)
	{
		wall = doom->sectors[sect].wall[i];
		if (check_collsion(doom, motion, wall, &point))
		{
			if (wall->solid || wall->n == -1)
				return (1);
			if (doom->sectbool[wall->n] == FALSE)
			{
				if (check_portal(doom, motion, wall, point))
					return (2);
				doom->sectbool[wall->n] = TRUE;
				if (check_solid_surfaces_no_slide(doom, motion, wall->n))
					return (3);
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
	if (!check_solid_surfaces_no_slide(doom, &new, new.curr_sect))
	{
		motion->velocity.x = new.velocity.x;
		motion->velocity.y = new.velocity.y;
		return (0);
	}
	return (1);
}
