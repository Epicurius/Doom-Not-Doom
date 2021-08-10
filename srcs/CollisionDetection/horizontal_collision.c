/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_collision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:56:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/10 12:05:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
				if (check_solid_surfaces(doom, motion, wall->n))
					return (1);
			}
		}
	}
	return (0);
}
