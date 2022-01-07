/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:04:26 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/07 16:20:51 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Find sector centroid.
 */
void	sector_center(t_sector *sector)
{
	int		i;
	float	a;
	float	t;

	i = -1;
	a = 0.0f;
	while (++i < sector->npoints)
	{
		t = sector->wall[i]->v1.x * sector->wall[i]->v2.y
			- sector->wall[i]->v2.x * sector->wall[i]->v1.y;
		a += t;
		sector->center.x += (sector->wall[i]->v1.x + sector->wall[i]->v2.x) * t;
		sector->center.y += (sector->wall[i]->v1.y + sector->wall[i]->v2.y) * t;
	}
	sector->center.x /= 6.0 * (a * 0.5);
	sector->center.y /= 6.0 * (a * 0.5);
}

/*
 *	Fixes wall so wall vertices are clockwise.
 */
void	fix_wall_orientation(t_sector *sector)
{
	int		i;
	t_v3	temp;

	i = -1;
	while (++i < sector->npoints)
	{
		if (point_side_v2(sector->wall[i]->v1, sector->wall[i]->v2,
				sector->center) < 0)
		{
			temp = sector->wall[i]->v2;
			sector->wall[i]->v2 = sector->wall[i]->v1;
			sector->wall[i]->v1 = temp;
		}
	}
}

/*
 *	Fixes wall order so each wall has its left and right wall next to it.
 */
static int	fix_wall_order2(t_sector *sector, int i, t_v3 v2)
{
	int		j;
	t_wall	*temp;

	j = i;
	while (++j < sector->npoints)
	{
		if (comp_v3(v2, sector->wall[j]->v1))
		{
			temp = sector->wall[i];
			sector->wall[i] = sector->wall[j];
			sector->wall[j] = temp;
			return (1);
		}
	}
	LG_WARN("Sector %d wall %d coordinates don't match up!\n", sector->id, i);
	return (0);
}

int	fix_wall_order(t_sector *sector)
{
	int		i;
	t_v3	v2;

	i = 0;
	v2 = sector->wall[i]->v2;
	while (++i <= sector->npoints)
	{
		if (comp_v3(v2, sector->wall[i % sector->npoints]->v1))
		{
			v2 = sector->wall[i % sector->npoints]->v2;
			continue ;
		}
		if (!fix_wall_order2(sector, i, v2))
			return (0);
		i -= 1;
	}
	return (1);
}

/*
 *	Checks if sector is convex.
 */
int	is_convex(t_sector *sector)
{
	int		i;
	int		n;
	float	prev;
	float	curr;

	i = -1;
	prev = 0;
	curr = 0;
	n = sector->npoints;
	while (++i < sector->npoints)
	{
		curr = point_side_v2(sector->wall[(i + 1) % n]->v1,
				sector->wall[(i + 2) % n]->v1, sector->wall[i]->v1);
		if (curr != 0)
		{
			if (curr * prev < 0)
			{
				LG_WARN("Sector %d is concave, must be convex!\n", sector->id);
				return (0);
			}
			prev = curr;
		}
	}
	return (1);
}
