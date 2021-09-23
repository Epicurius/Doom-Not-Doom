/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_sector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:20:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/23 11:17:43 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Parse vertice.
 */
void	parse_vertex(t_doom *doom, int nb, char **arr)
{
	if (nb < 2)
		error_msg("Invalid amount of vertex arguments %s\n", arr[0]);
	doom->vert[ft_atoi(arr[0])].x = ft_atof(arr[1]) * doom->map_scale;
	doom->vert[ft_atoi(arr[0])].y = ft_atof(arr[2]) * doom->map_scale;
}

/*
 *	Parse wall.
 */
void	parse_wall(t_doom *doom, int nb, char **arr)
{
	t_wall	*wall;

	if (nb < 7)
		error_msg("Invalid amount of wall arguments %s\n", arr[0]);
	wall = &doom->walls[ft_atoi(arr[0])];
	wall->v1 = doom->vert[ft_atoi(arr[1])];
	wall->v2 = doom->vert[ft_atoi(arr[2])];
	wall->wtx = ft_atoi(arr[3]);
	wall->ptx = ft_atoi(arr[4]);
	wall->scale_factor = ft_atof(arr[5]) * doom->map_scale;
	wall->solid = ft_atoi(arr[6]);
}

/*
 *	Parse floor and ceiling.
 */
void	parse_fc(t_doom *doom, int nb, char **arr)
{
	int		sect;
	char	**slope;
	t_plane	*floor;
	t_plane	*ceiling;

	if (nb < 8)
		error_msg("Invalid amount of f&c arguments %s\n", arr[0]);
	sect = ft_atoi(arr[0]);
	floor = &doom->sectors[sect].floor;
	ceiling = &doom->sectors[sect].ceiling;
	floor->height = atof(arr[1]) * doom->map_scale;
	ceiling->height = atof(arr[2]) * doom->map_scale;
	floor->tx = ft_atoi(arr[3]);
	ceiling->tx = ft_atoi(arr[4]);
	floor->scale = atof(arr[5]) * doom->map_scale;
	ceiling->scale = atof(arr[6]) * doom->map_scale;
	slope = stringsplit(arr[7], ' ', NULL);
	doom->sectors[sect].floor_incl_start = ft_atoi(slope[0]);
	doom->sectors[sect].floor_incl_angle = ft_atoi(slope[1])
		* CONVERT_TO_RADIANS;
	doom->sectors[sect].ceiling_incl_start = ft_atoi(slope[2]);
	doom->sectors[sect].ceiling_incl_angle = ft_atoi(slope[3])
		* CONVERT_TO_RADIANS;
	free(slope);
}

/*
 *	Link wall to sector walls.
 */
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

/*
 *	Parse sector.
 */
void	parse_sector(t_doom *doom, int ac, char **arr)
{
	int			nb;
	t_sector	*sect;
	char		**walls;
	char		**neighbour;

	if (ac < 5)
		error_msg("Invalid amount of sector arguments %s\n", arr[0]);
	sect = &doom->sectors[ft_atoi(arr[0])];
	sect->id = ft_atoi(arr[0]);
	walls = stringsplit(arr[1], ' ', &sect->npoints);
	sect->wall = PROT_ALLOC(sizeof(t_wall *) * (sect->npoints));
	neighbour = stringsplit(arr[2], ' ', &nb);
	if (nb != sect->npoints)
		error_msg("Sect %d walls != Neighbours.\n", sect->id);
	sect->gravity = ft_atoi(arr[3]) * 1.5;
	sect->light = ft_atoi(arr[4]);
	sect->trigger = FALSE;
	complete_wall(sect, doom->walls, walls, neighbour);
	free(walls);
	free(neighbour);
}
