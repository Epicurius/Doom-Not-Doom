/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_wall_sector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:31:33 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/26 13:00:54 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	wall_to_screen_xz(t_game_player player, t_game_wall *wall)
{
	t_xyz v1;
	t_xyz v2;

	/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
	/* Rotate correctly hte map into players view */
	v1.x = wall->v1.x - player.where.x;
	v1.y = wall->v1.y - player.where.y;
	v2.x = wall->v2.x - player.where.x;
	v2.y = wall->v2.y - player.where.y;
	wall->sv1.x = v1.x * player.anglesin - v1.y * player.anglecos;
	wall->sv1.z = v1.x * player.anglecos + v1.y * player.anglesin;
	wall->sv2.x = v2.x * player.anglesin - v2.y * player.anglecos;
	wall->sv2.z = v2.x * player.anglecos + v2.y * player.anglesin;

}
