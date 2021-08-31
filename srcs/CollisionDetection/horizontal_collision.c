/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_collision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:56:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/31 11:52:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Check portal dimension on the closest point of the wall to the entity.
 */
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

/*
 *	Check if entity intersects wall or that its hitbox touches the wall.
 */
int	check_collsion(t_motion *motion, t_wall *wall, t_v3 *point)
{
	*point = closest_point_on_segment_v2(motion->dest, wall->v1, wall->v2);
	if (intersect_v2(motion->where, motion->dest, wall->v1, wall->v2))
		return (1);
	if (point_distance_v2(point->x, point->y, motion->dest.x, motion->dest.y)
		<= DIAMETER)
		return (2);
	return (0);
}

/*
 *	Check all the solid surfaces that the hitbox collides with.
 *	Solid wall or portal bottom half or portal top half.
 *	If there is collision try sliding parallel to the wall.
 */
int	check_solid_surfaces(t_doom *doom, t_motion *motion, int sect)
{
	int		i;
	t_v3	point;
	t_wall	*wall;

	i = -1;
	while (++i < doom->sectors[sect].npoints)
	{
		wall = doom->sectors[sect].wall[i];
		if (check_collsion(motion, wall, &point))
		{
			if (wall->solid || wall->n == -1)
				return (slide_collision(doom, motion, wall));
			if (doom->sectbool[wall->n] == FALSE)
			{
				if (check_portal(doom, motion, wall, point))
					return (slide_collision(doom, motion, wall));
				doom->sectbool[wall->n] = TRUE;
				if (horizontal_collision(doom, motion, wall->n))
					return (1);
			}
		}
	}
	return (0);
}

/*
 *	Find the correct sector from the sectbool list of sectors
 *	that player hitbox has moved through.
 *	If none of the match, check all sectors.
 *	If that fales return -1, to kill the entity.
 */
int	find_from_sectbool(t_doom *doom, t_motion *motion)
{
	int		i;
	t_v3	where;

	i = -1;
	where = add_v3(motion->where, motion->velocity);
	while (++i < doom->nb.sectors)
	{
		if (doom->sectbool[i] && in_sector_area(&doom->sectors[i], where))
			return (i);
	}
	ft_printf("{RED}[ERROR]{RESET}\tWrong Sector\n");
	return (find_sector_no_z(doom->sectors, doom->nb.sectors, where));
}

int	horizontal_collision(t_doom *doom, t_motion *motion, int sect)
{
	if (!check_solid_surfaces(doom, motion, motion->sector))
	{
		motion->sector = find_from_sectbool(doom, motion);
		if (motion->sector == -1)
			return (-1);
	}
	else
	{
		motion->velocity.x = 0;
		motion->velocity.y = 0;
	}
	return (0);
}
