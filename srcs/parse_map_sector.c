/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_sector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:20:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/21 18:11:05 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//		doom->vert[ft_atoi(arr[0])].z = ft_atof(arr[3]) * doom->map_scale;
void	parse_vertex(t_doom *doom, char **arr)
{
	doom->vert[ft_atoi(arr[0])].x = ft_atof(arr[1]) * doom->map_scale;
	doom->vert[ft_atoi(arr[0])].y = ft_atof(arr[2]) * doom->map_scale;
}

void	parse_wall(t_doom *doom, char **arr)
{
	t_wall	*wall;

	wall = &doom->walls[ft_atoi(arr[0])];
	wall->v1 = doom->vert[ft_atoi(arr[1])];
	wall->v2 = doom->vert[ft_atoi(arr[2])];
	wall->wtx = ft_atoi(arr[3]);
	wall->ptx = ft_atoi(arr[4]);
	wall->scale = ft_atof(arr[5]) * doom->map_scale;
	wall->solid = ft_atoi(arr[6]);
}

void	parse_fc(t_doom *doom, char **arr)
{
	int		sect;
	char	**slope;
	t_plane	*floor;
	t_plane	*ceiling;

	sect = ft_atoi(arr[0]);
	floor = &doom->sectors[sect].floor;
	ceiling = &doom->sectors[sect].ceiling;
	floor->y = atof(arr[1]) * doom->map_scale;
	ceiling->y = atof(arr[2]) * doom->map_scale;
	floor->tx = ft_atoi(arr[3]);
	floor->scale = atof(arr[4]) * doom->map_scale;
	ceiling->tx = ft_atoi(arr[5]);
	ceiling->scale = atof(arr[6]) * doom->map_scale;
	slope = ft_strsplit(arr[7], ' ', NULL);
	doom->sectors[sect].wall_floor_slope = ft_atoi(slope[0]);
	doom->sectors[sect].floor_slope = ft_atoi(slope[1]) * CONVERT_RADIANS;
	doom->sectors[sect].wall_ceiling_slope = ft_atoi(slope[2]);
	doom->sectors[sect].ceiling_slope = ft_atoi(slope[3]) * CONVERT_RADIANS;
	free(slope);
}

void	complete_wall(t_sector *sect, t_wall *walls, char **id,
		char **neighbour)
{
	int	l;
	int	wall_nb;

	l = -1;
	while (++l < sect->npoints)
	{
		wall_nb = ft_atoi(id[l]);
		sect->wall[l] = &walls[wall_nb];
		sect->wall[l]->id = wall_nb;
		sect->wall[l]->sect = sect->id;
		sect->wall[l]->n = ft_atoi(neighbour[l]);
	}
}

void	parse_sector(t_doom *doom, char **arr)
{
	int			nb;
	t_sector	*sect;
	char		**walls;
	char		**neighbour;

	sect = &doom->sectors[ft_atoi(arr[0])];
	sect->id = ft_atoi(arr[0]);
	walls = ft_strsplit(arr[1], ' ', &sect->npoints);
	sect->wall = ft_pmalloc(sizeof(t_wall *) * (sect->npoints), "parse_sector");
	neighbour = ft_strsplit(arr[2], ' ', &nb);
	if (nb != sect->npoints)
		error_msg("Sect %d walls != Neighbours.\n", sect->id);
	sect->gravity = ft_atoi(arr[3]) / 1000.0;
	sect->light = ft_atoi(arr[4]);
	complete_wall(sect, doom->walls, walls, neighbour);
	free(walls);
	free(neighbour);
}
