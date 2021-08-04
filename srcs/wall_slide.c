/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_slide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 10:59:44 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/04 09:54:25 by nneronin         ###   ########.fr       */
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

static int	horizontal_slide_collision(t_doom *doom, t_motion motion,
	t_v3 velocity)
{
	int		i;
	t_wall	*wall;

	i = -1;
	motion.future = add_v3(motion.where, velocity);
	while (++i < doom->sectors[motion.curr_sect].npoints)
	{
		wall = doom->sectors[motion.curr_sect].wall[i];
		if (wall->solid || wall->n == -1)
		{
			if (intersect_check_v2(motion.where, motion.future,
					wall->v1, wall->v2))
				return (1);
			else if (hitbox_collision(motion.future, wall->v1, wall->v2, 1.0))
				return (2);
		}
		else if (hitbox_collision(motion.future, wall->v1, wall->v2, 1.0))
			return (3);
	}
	return (0);
}

void	slide_collision(t_doom *doom, t_motion *motion, t_wall *wall, int slide)
{
	t_v3	velocity;

	if (slide == FALSE)
		return ;
	velocity = parallel_movement(motion->velocity, wall->v1, wall->v2);
	if (!horizontal_slide_collision(doom, *motion, velocity))
	{
		motion->move = velocity;
		motion->velocity = velocity;
	}
}
