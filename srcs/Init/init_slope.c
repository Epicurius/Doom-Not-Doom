/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_slope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 10:06:20 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/17 17:35:45 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

TEMP_FLOAT	ceiling_at(t_sector *sector, t_v3 pos)
{
	TEMP_FLOAT	peq;
	t_v3	v;

	v = sector->wall[sector->wall_ceiling_slope]->v1;
	peq = sector->ceiling_normal.x * (pos.x - v.x)
		- sector->ceiling_normal.y * (pos.y - v.y);
	return (peq * sector->ceiling_slope + sector->ceiling.y);
}

TEMP_FLOAT	floor_at(t_sector *sector, t_v3 pos)
{
	TEMP_FLOAT	peq;
	t_v3	v;

	v = sector->wall[sector->wall_floor_slope]->v1;
	peq = sector->floor_normal.x * (pos.x - v.x)
		- sector->floor_normal.y * (pos.y - v.y);
	return (peq * sector->floor_slope + sector->floor.y);
}

//		normal of 2 vectors will be the slope direction (unit vectort normal)
static t_v2	get_unit_normal_vector(t_sector *sector, int wall)
{
	t_v3	v1;
	t_v3	v2;
	t_v2	normal;
	TEMP_FLOAT	m;

	v1 = sector->wall[wall]->v1;
	v2 = sector->wall[wall]->v2;
	m = point_distance_v2(v1.x, v1.y, v2.x, v2.y);
	normal.x = -((v2.y - v1.y) / m);
	normal.y = -((v2.x - v1.x) / m);
	return (normal);
}

void	init_slope_normal(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		doom->sectors[i].floor_normal = get_unit_normal_vector(
				&doom->sectors[i], doom->sectors[i].wall_floor_slope);
		doom->sectors[i].ceiling_normal = get_unit_normal_vector(
				&doom->sectors[i], doom->sectors[i].wall_ceiling_slope);
	}
}
