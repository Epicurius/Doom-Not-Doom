/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:04:26 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/25 09:45:25 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//		sector->center.z = (sector->ceiling.y - sector->floor.y) / 2.0;
void	sector_center(t_sector *sector)
{
	int	i;

	i = -1;
	while (++i < sector->npoints)
	{
		sector->center.x += sector->wall[i]->v1.x;
		sector->center.y += sector->wall[i]->v1.y;
	}
	sector->center.x /= sector->npoints;
	sector->center.y /= sector->npoints;
	sector->center.z = get_floor_at_pos(sector, sector->center);
}

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
	ft_printf("{YELLOW}[INFO]{RESET} Sector %d wall %d "
		"coordinates don't match up!\n", sector->id, i);
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

int	is_convex(t_sector *sector)
{
	int		i;
	int		n;
	double	prev;
	double	curr;

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
				ft_printf("{YELLOW}[INFO]{RESET} Sector %d is concave, "
					"must be convex!\n", sector->id);
				return (0);
			}
			prev = curr;
		}
	}
	return (1);
}
