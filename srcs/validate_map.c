/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clockwise_order.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 10:12:36 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/17 14:47:27 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	sector_center(t_sector *sector)
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

void	fix_wall_orientation(t_sector *sector)
{
	int i;
	t_xyz temp;

	i = -1;
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
	ft_printf("{RED}[ERROR]{RESET} Sector %d wall %d coordinates don't match up!\n", sector->id, i);
	return (0);
}

int	fix_wall_order(t_sector *sector)
{
	int		i;
	int		j;
	t_xyz	v2;

	i = 0;
	v2 = sector->wall[i]->v2;
	while (++i <= sector->npoints)
	{
		if (compare_xyz(v2, sector->wall[i % sector->npoints]->v1))
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
			{
				ft_printf("{RED}[ERROR]{RESET} Sector %d is convex!\n", sector->id);
				return (0);
			}
			prev = curr;
		}
	}
	return (1);
}

int check_entities(t_doom *doom)
{
	t_list		*curr;

	curr = doom->sprite;
	while (curr)
	{
		((t_entity *)curr->content)->sector =
			find_sector(doom, ((t_entity *)curr->content)->where);
		if (((t_entity *)curr->content)->sector < 0)
			return (0);
		curr = curr->next;
	}
	return (1);
}

int check_player(t_doom *doom)
{
	doom->player.sector = find_sector(doom, doom->player.where);
	if (doom->player.sector < 0)
		return (0);
	return (1);
}

int check_map(t_doom *doom)
{
	int i;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		sector_center(&doom->sectors[i]);
		fix_wall_orientation(&doom->sectors[i]);
		if (!fix_wall_order(&doom->sectors[i]))
			return (0);
		if (!is_convex(&doom->sectors[i]))
			return (0);
	}
	return (1);
}


int		validate_map(t_doom *doom)
{
	if (check_map(doom) &&
		check_player(doom) &&
		check_entities(doom))
		return (1);
	doom->quit = -1;
	return (0);
	//check_textures();
}
