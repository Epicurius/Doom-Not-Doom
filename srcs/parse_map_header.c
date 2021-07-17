/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:18:33 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/17 19:07:54 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	parse_header(t_doom *doom, char **arr)
{
	doom->map_scale = ft_atoi(arr[2]);
	doom->nb.vertices = ft_atoi(arr[3]);
	doom->nb.walls = ft_atoi(arr[4]);
	doom->nb.sectors = ft_atoi(arr[5]);
	doom->nb.entities = 0;
	doom->nb.projectiles = 0;
	doom->nb.rifts = 0;
	doom->orb = NULL;
	doom->entity = NULL;
	doom->rifts = NULL;
	doom->vert = ft_pmalloc(sizeof(t_v3)
			* doom->nb.vertices, "doom->vert");
	doom->walls = ft_pmalloc(sizeof(t_wall)
			* doom->nb.walls, "doom->walls");
	doom->sectors = ft_pmalloc(sizeof(t_sector)
			* doom->nb.sectors, "doom->sectors");
}
