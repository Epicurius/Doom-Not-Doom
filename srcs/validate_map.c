/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 10:12:36 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/18 11:42:51 by nneronin         ###   ########.fr       */
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

void	fix_wall_order2(t_doom *doom, t_sector *sector, int i, t_xyz v2)
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
			return ;
		}
	}
	error_msg("Sector %d wall %d coordinates don't match up!\n", sector->id, i);
}

void	fix_wall_order(t_doom *doom, t_sector *sector)
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
		fix_wall_order2(doom, sector, i, v2);
		i -= 1;
	}
}

void	is_convex(t_doom *doom, t_sector *sector)
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
				error_msg("Sector %d is convex!\n", sector->id);
			prev = curr;
		}
	}
}

void	check_entities(t_doom *doom)
{
	t_list		*curr;

	curr = doom->sprite;
	while (curr)
	{
		((t_entity *)curr->content)->sector =
			find_sector(doom, ((t_entity *)curr->content)->where);
		if (((t_entity *)curr->content)->sector < 0)
			error_msg("Entity is outside map boundaries!\n");
		curr = curr->next;
	}
}

void	check_player(t_doom *doom)
{
	doom->player.sector = find_sector(doom, doom->player.where);
	if (doom->player.sector < 0)
		error_msg("Player is outside map boundaries!\n");
}

void	check_map(t_doom *doom)
{
	int i;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		sector_center(&doom->sectors[i]);
		fix_wall_orientation(&doom->sectors[i]);
		fix_wall_order(doom, &doom->sectors[i]);
		is_convex(doom, &doom->sectors[i]);
	}
}


void	validate_map(t_doom *doom)
{
	check_map(doom);
	check_player(doom);
	check_entities(doom);
	//check_textures();
}
