/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clockwise_order.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 10:12:36 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/11 17:28:51 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	sector_center(t_sector *sector)
{
	int		i;
	t_xyz	c;

	i = -1;
	while (++i < sector->npoints)
	{
		sector->center.x += sector->wall[i]->v1.x;
		sector->center.y += sector->wall[i]->v1.y;
	}
	sector->center.x /= sector->npoints;
	sector->center.y /= sector->npoints;
	sector->center.z = (sector->ceiling.y - sector->floor.y) / 2.0;
}

static void	fix_wall_orientation(t_sector *sector)
{
	int i;
	t_xyz v1;
	t_xyz v2;
	t_xyz temp;

	i = 0;
	v1 = sector->wall[i]->v1;
	v2 = sector->wall[i]->v2;
	while (++i < sector->npoints)
	{
		if (point_side(sector->wall[i]->v1, sector->wall[i]->v2, sector->center) < 0)
		{
			temp = sector->wall[i]->v2;
			sector->wall[i]->v2 = sector->wall[i]->v1;
			sector->wall[i]->v1 = temp;
		}
	}
}

int	fix_wall_order2(t_sector *sector, int i, t_xyz v2)
{
	int		j;
	t_wall	*temp;

	j = i;
	while (++j < sector->npoints)
	{
		if (compare_xyz(v2, sector->wall[j]->v1))
		{
			temp = sector->wall[i];
			sector->wall[i] = sector->wall[j];
			sector->wall[j] = temp;
			return (1);
		}
	}
	return (0);
}

int	fix_wall_order(t_sector *sector)
{
	int		i;
	int		j;
	t_xyz	v2;

	i = 0;
	v2 = sector->wall[i]->v2;
	while (++i < sector->npoints)
	{
		if (compare_xyz(v2, sector->wall[i]->v1))
		{
			v2 = sector->wall[i]->v2;
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
	int i;
	int n;
    double prev;
    double curr;

   	i = -1;
	prev = 0;
	curr = 0;
    n = sector->npoints;
	while (++i < sector->npoints)
	{
		curr = (sector->wall[(i + 1) % n]->v1.x - sector->wall[i]->v1.x) *
				(sector->wall[(i + 2) % n]->v1.y - sector->wall[i]->v1.y) -
				(sector->wall[(i + 1) % n]->v1.y - sector->wall[i]->v1.y) *
				(sector->wall[(i + 2) % n]->v1.x - sector->wall[i]->v1.x);
        if (curr != 0)
		{
            if (curr * prev < 0)
                return (1);
			prev = curr;
        }
    }
    return (0);
}

int	fix_map(t_doom *doom)
{
	int i;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		sector_center(&doom->sectors[i]);
		fix_wall_orientation(&doom->sectors[i]);
		if (!fix_wall_order(&doom->sectors[i]))
			return (ft_printf("[ERROR] Sector %d walls are wrong!\n", i));
		if (is_convex(&doom->sectors[i]))
			return (ft_printf("[ERROR] Sector %d is convex!\n", i));
	}
	return (0);
}
