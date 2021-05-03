/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:18:33 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/03 13:29:37 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	parse_header(t_doom *doom, char **arr)
{
	doom->map_scale		= ft_atof(arr[1]);
	doom->nb.vertices	= ft_atoi(arr[2]);
	doom->nb.walls		= ft_atoi(arr[3]);
	doom->nb.sectors	= ft_atoi(arr[4]);
	doom->nb.sprites	= 0;
	doom->nb.projectiles	= 0;
	doom->nb.rifts	= 0;
	doom->vert	= ft_memalloc(sizeof(t_xyz) * doom->nb.vertices);
	doom->walls	= ft_memalloc(sizeof(t_wall) * doom->nb.walls);
	doom->sectors	= ft_memalloc(sizeof(t_sector) * doom->nb.sectors);
	doom->orb = NULL;
	doom->sprite = NULL;
	doom->rifts = NULL;
}
