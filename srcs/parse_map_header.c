/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:18:33 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/15 16:18:55 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	parse_header(t_doom *doom, char **arr)
{
	doom->map_scale		= ft_atof(arr[2]);
	doom->nb.vertices	= ft_atoi(arr[3]);
	doom->nb.walls		= ft_atoi(arr[4]);
	doom->nb.sectors	= ft_atoi(arr[5]);
	doom->nb.sprites	= 0;
	doom->nb.projectiles	= 0;
	doom->nb.rifts	= 0;
	doom->vert = ft_memalloc(sizeof(t_xyz) * doom->nb.vertices);
	doom->walls = ft_memalloc(sizeof(t_wall) * doom->nb.walls);
	doom->sectors = ft_memalloc(sizeof(t_sector) * doom->nb.sectors);
	doom->orb = NULL;
	doom->sprite = NULL;
	doom->rifts = NULL;
	if (!doom->vert || !doom->walls || !doom->sectors)
		error_msg("Map malloc.\n");
	ft_printf("v:%d w:%d s:%d\n", doom->nb.vertices, doom->nb.walls, doom->nb.sectors);
}
