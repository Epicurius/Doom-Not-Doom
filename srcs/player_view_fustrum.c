/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view_fustrum.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:22:47 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/12 15:58:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_xyz		intersect(t_xyz s[2], float x3, float y3, float x4, float y4)
{
	t_xyz xy;

	xy.z =	0;
    xy.x =	vxs(vxs(s[0].x, s[0].y, s[1].x, s[1].y), s[0].x - s[1].x,
			vxs(x3, y3, x4, y4), x3 - x4) /
			vxs(s[0].x - s[1].x, s[0].y - s[1].y, x3 - x4, y3 - y4);
	xy.y =	vxs(vxs(s[0].x, s[0].y, s[1].x, s[1].y), s[0].y - s[1].y,
			vxs(x3, y3, x4, y4), y3 - y4) /
			vxs(s[0].x - s[1].x, s[0].y - s[1].y, x3 - x4, y3 - y4);
	return (xy);
}

/* If it's partially behind the player, clip it against player's view frustrum */
void	player_view_fustrum(t_doom *doom, t_scale *viewpoint)
{
	t_xyz i1;
	t_xyz i2;

	t_xyz org1 = (t_xyz){.x = viewpoint->edges[0].x, .y = viewpoint->edges[0].y, .z = 0};
	t_xyz org2 = (t_xyz){.x = viewpoint->edges[1].x, .y = viewpoint->edges[1].y, .z = 0};
	i1 = intersect(viewpoint->edges, -NEARSIDE, NEARZ, -FARSIDE, FARZ);
	i2 = intersect(viewpoint->edges, NEARSIDE, NEARZ, FARSIDE, FARZ);
	if (viewpoint->edges[0].y < NEARZ)
	{
		if (i1.y > 0)
			viewpoint->edges[0] = (t_xyz){.x = i1.x, .y = i1.y};
		else
			viewpoint->edges[0] = (t_xyz){.x = i2.x, .y = i2.y};
	}
	if (viewpoint->edges[1].y < NEARZ)
	{
		if (i1.y > 0)
			viewpoint->edges[1] = (t_xyz){.x = i1.x, .y = i1.y};
		else
			viewpoint->edges[1] = (t_xyz){.x = i2.x, .y = i2.y};
	}
	//Cut the texture if smaller wall smaller than texture
	if (fabsf(viewpoint->edges[1].x - viewpoint->edges[0].x) > fabsf(viewpoint->edges[1].y - viewpoint->edges[0].y))
	{
		doom->u0 = (viewpoint->edges[0].x - org1.x) * doom->u1 / (org2.x - org1.x);
		doom->u1 = (viewpoint->edges[1].x - org1.x) * doom->u1 / (org2.x - org1.x);
	}
	else
	{
		doom->u0 = (viewpoint->edges[0].y - org1.y) * doom->u1 / (org2.y - org1.y);
		doom->u1 = (viewpoint->edges[1].y - org1.y) * doom->u1 / (org2.y - org1.y);
	}
}
