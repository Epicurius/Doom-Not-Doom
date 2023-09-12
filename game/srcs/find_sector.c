/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Checks it pos(x,y,z) is in given sector.
 *	For this to work all walls have to be in order.
 */
int	in_sector(t_sector *sector, t_v3 pos)
{
	int		i;

	i = -1;
	if (floor_at(sector, pos) > pos.z || ceiling_at(sector, pos) < pos.z)
		return (0);
	while (++i < sector->npoints)
	{
		if (point_side_v2(sector->wall[i]->v1, sector->wall[i]->v2, pos) < 0.0)
			return (0);
	}
	return (1);
}

/*
 *	Loops through all sectors and checks if pos(x,y,z) is in it.
 *	Returns pos sector or -1 if pos is none of the sectors.
 */
int	find_sector(t_sector *sectors, int nb, t_v3 pos)
{
	int	i;

	i = -1;
	while (++i < nb)
	{
		if (in_sector(&sectors[i], pos))
			return (i);
	}
	return (-1);
}

/*
 *	Checks it pos(x,y) is in given sector.
 *	For this to work all walls have to be in order.
 */
int	in_sector_area(t_sector *sector, t_v3 pos)
{
	int		i;

	i = -1;
	while (++i < sector->npoints)
	{
		if (point_side_v2(sector->wall[i]->v1, sector->wall[i]->v2, pos) < 0.0)
			return (0);
	}
	return (1);
}

/*
 *	Loops through all sectors and checks if pos(x,y) is in it.
 *	Returns pos sector or -1 if pos is none of the sectors.
 */
int	find_sector_no_z(t_sector *sectors, int nb, t_v3 pos)
{
	int	i;

	i = -1;
	while (++i < nb)
	{
		if (in_sector_area(&sectors[i], pos))
			return (i);
	}
	return (-1);
}
