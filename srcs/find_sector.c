/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:50:54 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/14 18:57:44 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		in_sector(t_sector *sector, t_xyz pos)
{
	int i;
	double p;

	i = -1;
	//if (sector->floor.y > pos.z || sector->ceiling.y < pos.z)//Fix
	if (get_floor_at_pos(sector, pos) > pos.z || get_ceiling_at_pos(sector, pos) < pos.z)
	{
	//	printf("pos:(%f %f %f | %d)", pos.x, pos.y, pos.z, sector->id);
	//	printf("\tfc:(%f %f)\n", get_floor_at_pos(sector, pos), get_ceiling_at_pos(sector, pos));
		return (0);
	}
	while (++i < sector->npoints)
	{
		if (point_side(sector->wall[i]->v1, sector->wall[i]->v2, pos) < 0)
			return (0);
	}
	return (1);
}

int		find_sector(t_doom *doom, t_xyz pos)
{
	int	i;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		if (in_sector(&doom->sectors[i], pos))
			return (i);
	}
	return (-1);
}
