/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_sector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:20:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/01 16:17:55 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	parse_vertex(t_doom *doom, char **arr)
{
	doom->vert[ft_atoi(arr[0])].x = ft_atof(arr[1]) * doom->map_scale;
	doom->vert[ft_atoi(arr[0])].y = ft_atof(arr[2]) * doom->map_scale;
	doom->vert[ft_atoi(arr[0])].z = ft_atof(arr[3]) * doom->map_scale;
}

void	parse_wall(t_doom *doom, char **arr)
{
	t_wall	*wall;

	wall		= &doom->walls[ft_atoi(arr[0])];
	wall->v1	= doom->vert[ft_atoi(arr[1])];
	wall->v2	= doom->vert[ft_atoi(arr[2])];
	wall->wtx	= ft_atoi(arr[3]);
	wall->ptx	= ft_atoi(arr[4]);
	wall->scale	= ft_atof(arr[5]) * doom->map_scale;
	wall->solid	= ft_atoi(arr[6]);
}

void	parse_fc(t_doom *doom, char **arr)
{
	int		sect;
	t_plane	*floor;
	t_plane	*ceiling;

	sect			= ft_atoi(arr[1]);
	floor			= &doom->sectors[sect].floor;
	ceiling			= &doom->sectors[sect].ceiling;
	floor->y		= atof(arr[2]) * doom->map_scale;
	ceiling->y		= atof(arr[3]) * doom->map_scale;
	floor->tx		= ft_atoi(arr[4]);
	ceiling->tx		= ft_atoi(arr[5]);
	floor->scale	= atof(arr[6]) * doom->map_scale;
	ceiling->scale	= atof(arr[6]) * doom->map_scale;
}

void	complete_wall(t_sector *sect, t_wall *walls, char **id, char **neighbour)
{
	int l;
	int wall_nb;

	l = -1;
	while (++l < sect->npoints)
	{
		wall_nb					= ft_atoi(id[l]);
		sect->wall[l]			= &walls[wall_nb];
		sect->wall[l]->id		= wall_nb;
		sect->wall[l]->sect		= sect->id;
		sect->wall[l]->n		= ft_atoi(neighbour[l]);
	}
}

void	parse_sector(t_doom *doom, char **arr)
{
	t_sector	*sect;
	char		**walls;
	char		**neighbour;

	sect			= &doom->sectors[ft_atoi(arr[0])];
	sect->id		= ft_atoi(arr[0]);
	walls			= ft_strsplit(arr[1], ' ');
	sect->npoints	= ft_strarr_func(walls, NULL);
	sect->wall		= ft_memalloc(sizeof(t_wall*) * (sect->npoints));
	neighbour		= ft_strsplit(arr[2], ' ');
	sect->gravity	= ft_atoi(arr[3]) / 1000.0;
	sect->light		= ft_atoi(arr[4]);
	complete_wall(sect, doom->walls, walls, neighbour);
	ft_strarr_func(walls, ft_strdel);
	ft_strarr_func(neighbour, ft_strdel);
	free(walls);
	free(neighbour);
}
