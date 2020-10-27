/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_wall_sector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:31:33 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/27 14:38:52 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	rotate_wall_sector(t_sector *sect, int s, t_player *player, t_xyz t[2])
{
	t_xyz v1;
	t_xyz v2;

	/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
	/* Rotate correctly hte map into players view */
	v1.x = sect->vertex[s + 0].x - player->where.x;
	v1.y = sect->vertex[s + 0].y - player->where.y;
	v2.x = sect->vertex[s + 1].x - player->where.x;
	v2.y = sect->vertex[s + 1].y - player->where.y;
	t[0].x = v1.x * player->anglesin - v1.y * player->anglecos;
	t[0].z = v1.x * player->anglecos + v1.y * player->anglesin;
	t[1].x = v2.x * player->anglesin - v2.y * player->anglecos;
	t[1].z = v2.x * player->anglecos + v2.y * player->anglesin;
}
