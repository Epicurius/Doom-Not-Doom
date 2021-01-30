/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:22:10 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/19 10:19:01 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void move_player(t_doom *doom, float dx, float dy)
{
	int s;
	t_xyz p;
	t_xyz d;
	t_sector* sect;
	t_xyz* vert;

	s = -1;
	PLAYER.anglesin = sinf(PLAYER.yaw);
	PLAYER.anglecos = cosf(PLAYER.yaw);
	if (dx == 0.00f && dy == 0.00f)
		return ;
	p = (t_xyz){.x = PLAYER.where.x, .y = PLAYER.where.y, .z = 0};
	d = (t_xyz){.x = dx, .y = dy, .z = 0};
	sect = &doom->sectors[PLAYER.sector];
	vert = sect->vertex;
	while (++s < sect->npoints)
	{
        	if (sect->neighbors[s] >= 0 &&
			intersect_box(p, d, vert[s], vert[s + 1]) &&
			point_side(p, d, vert[s], vert[s + 1]) < 0)
        	{
			PLAYER.sector = sect->neighbors[s];
			break;
		}
	}
	PLAYER.where.x += dx;
	PLAYER.where.y += dy;
	//printf("%f, %f\n", PLAYER.where.x, PLAYER.where.y);
}
