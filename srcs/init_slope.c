/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_slope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 10:06:20 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/16 16:21:05 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	get_ceiling_at_pos(t_sector *sector, t_v3 pos)
{
	double	peq;
	t_v3	v;

	v = sector->wall[sector->wall_ceiling_slope]->v1;
	peq = sector->ceiling_normal.x * (pos.x - v.x)
		- sector->ceiling_normal.y * (pos.y - v.y);
	return (peq * sector->ceiling_slope + sector->ceiling.y);
}

double	get_floor_at_pos(t_sector *sector, t_v3 pos)
{
	double	peq;
	t_v3	v;

	v = sector->wall[sector->wall_floor_slope]->v1;
	peq = sector->floor_normal.x * (pos.x - v.x)
		- sector->floor_normal.y * (pos.y - v.y);
	return (peq * sector->floor_slope + sector->floor.y);
}

//			normal of 2 vectors will be the slope direction
t_v3	get_slope_normal(t_sector *sector, int wall)
{
	t_v3	v1;
	t_v3	v2;
	t_v3	normal;
	double	s;

	v1 = sector->wall[wall]->v1;
	v2 = sector->wall[wall]->v2;
	s = point_distance_2d(v1.x, v1.y, v2.x, v2.y);
	normal.x = -((v2.y - v1.y) / s);
	normal.y = -((v2.x - v1.x) / s);
	return (normal);
}

void	precompute_slopes(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		doom->sectors[i].floor_normal = get_slope_normal(&doom->sectors[i],
				doom->sectors[i].wall_floor_slope);
		doom->sectors[i].ceiling_normal = get_slope_normal(&doom->sectors[i],
				doom->sectors[i].wall_ceiling_slope);
	}
}
