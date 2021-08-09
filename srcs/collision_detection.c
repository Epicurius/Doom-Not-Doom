/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/09 16:54:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	hitbox_collision(t_v3 p, t_v3 v1, t_v3 v2, double radius)
{
	t_v3	point;

	point = closest_point_on_segment_v2(p, v1, v2);
	return ((point_distance_v2(point.x, point.y, p.x, p.y) <= radius));
}

int	check_solid_walls(t_doom *doom, t_motion *motion, int sect)
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
		point = closest_point_on_segment_v2(motion->future, wall->v1, wall->v2);
		if (intersect_v2(motion->where, motion->future, wall->v1, wall->v2)
			|| (point_distance_v2(point.x, point.y, motion->future.x, motion->future.y) <= DIAMETER))
		{
			if (wall->solid || wall->n == -1)
				return (1);
			if (doom->sectbool[wall->n] == FALSE)
			{
				pbot = ft_max(
						floor_at(&doom->sectors[sect], point),
						floor_at(&doom->sectors[wall->n], point));
				ptop = ft_min(
						ceiling_at(&doom->sectors[sect], point),
						ceiling_at(&doom->sectors[wall->n], point));
				if (ptop <= pbot + motion->height)
					return (2);
				if (ptop <= motion->future.z + motion->height || pbot > motion->future.z + STEP_HEIGHT)
					return (3);
				doom->sectbool[wall->n] = TRUE;
				if (check_solid_walls(doom, motion, wall->n))
					return (4);
			}
		}
	}
	return (0);
}

int	collision_detection(t_doom *doom, t_motion motion, t_v3 *where, t_v3 *velocity)
{
	//ft_printf("asdasdasdasdasdasdasdasd\n");
	motion.where = *where;
	motion.velocity = *velocity;
	motion.move = new_v3(0, 0, 0);
	if (vertical_collision(doom, &motion))
		return (-1);
	if (!(velocity->x == 0 && velocity->y == 0))
	{
		motion.future = add_v3(motion.where, motion.velocity);
		reset_sectbool(doom, motion.curr_sect);
		if (!check_solid_walls(doom, &motion, motion.curr_sect))
		{
			int i = -1;
			motion.move.x += motion.velocity.x;
			motion.move.y += motion.velocity.y;
			while (++i < doom->nb.sectors)
			{
				if (doom->sectbool[i] == TRUE && in_sector_area(&doom->sectors[i], add_v3(*where, motion.move)))
				{
					motion.curr_sect = i;
					break ;
				}
			}
			//reset_sectbool(doom, motion.curr_sect);
			//horizontal_collision(doom, &motion);
		}
	}
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
		motion.curr_sect = find_sector_no_z(doom->sectors, doom->nb.sectors, *where);
	}
	//ft_printf("yuiyuiyuiyuiy\n");
	return (motion.curr_sect);
}
