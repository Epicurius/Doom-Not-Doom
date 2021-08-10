/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:32:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/10 10:51:44 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	find_from_sectbool(t_doom *doom, t_motion motion)
{
	int		i;
	t_v3	where;

	i = -1;
	where = add_v3(motion.where, motion.velocity);
	while (++i < doom->nb.sectors)
	{
		if (doom->sectbool[i] && in_sector_area(&doom->sectors[i], where))
			return (i);
	}
	ft_printf("{RED}[ERROR]{RESET}\tWrong Sector\n");
	return (find_sector_no_z(doom->sectors, doom->nb.sectors, where));
}

int	check_portal(t_doom *doom, t_motion *motion, t_wall *wall, t_v3 point)
{
	t_fc	portal;

	portal.floor = ft_max(
			floor_at(&doom->sectors[wall->sect], point),
			floor_at(&doom->sectors[wall->n], point));
	portal.ceiling = ft_min(
			ceiling_at(&doom->sectors[wall->sect], point),
			ceiling_at(&doom->sectors[wall->n], point));
	if (portal.ceiling <= portal.floor + motion->height)
		return (1);
	if (portal.ceiling <= motion->dest.z + motion->height)
		return (2);
	if (portal.floor > motion->dest.z + motion->step)
		return (3);
	return (0);
}

int	check_collsion(t_doom *doom, t_motion *motion, t_wall *wall, t_v3 *point)
{
	*point = closest_point_on_segment_v2(motion->dest, wall->v1, wall->v2);
	if (intersect_v2(motion->where, motion->dest, wall->v1, wall->v2))
		return (1);
	if (point_distance_v2(point->x, point->y, motion->dest.x, motion->dest.y)
		<= DIAMETER)
		return (2);
	return (0);
}

int	check_solid_surfaces(t_doom *doom, t_motion *motion, int sect)
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
				return (slide_collision(doom, motion, wall));
			if (doom->sectbool[wall->n] == FALSE)
			{
				if (check_portal(doom, motion, wall, point))
					return (slide_collision(doom, motion, wall));
				doom->sectbool[wall->n] = TRUE;
				if (check_solid_surfaces(doom, motion, wall->n))
					return (1);
			}
		}
	}
	return (0);
}

int	collision_detection(t_doom *doom, t_motion motion,
	t_v3 *where, t_v3 *velocity)
{
	motion.step = 2;
	motion.where = *where;
	motion.velocity = *velocity;
	if (vertical_collision(doom, &motion))
		return (-1);
	if (!(velocity->x == 0 && velocity->y == 0))
	{
		motion.dest = add_v3(motion.where, motion.velocity);
		reset_sectbool(doom, motion.curr_sect);
		if (!check_solid_surfaces(doom, &motion, motion.curr_sect))
			motion.curr_sect = find_from_sectbool(doom, motion);
		else
			motion.velocity = new_v3(0, 0, motion.velocity.z);
	}
	if (motion.curr_sect == -1)
		return (-1);
	*velocity = motion.velocity;
	*where = add_v3(*where, *velocity);
	if (where->z < floor_at(&doom->sectors[motion.curr_sect], *where))
	{
		velocity->z = 0;
		where->z = floor_at(&doom->sectors[motion.curr_sect], *where);
	}
	return (motion.curr_sect);
}
