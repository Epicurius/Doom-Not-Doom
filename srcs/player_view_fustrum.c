/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view_fustrum.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:22:47 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/27 15:35:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_xyz		intersect(t_xyz s[2], float x3, float y3, float x4, float y4)
{
	t_xyz xy;

	xy.z =	0;
    xy.x =	vxs(vxs(s[0].x, s[0].z, s[1].x, s[1].z), s[0].x - s[1].x,
			vxs(x3, y3, x4, y4), x3 - x4) /
			vxs(s[0].x - s[1].x, s[0].z - s[1].z, x3 - x4, y3 - y4);
	xy.y =	vxs(vxs(s[0].x, s[0].z, s[1].x, s[1].z), s[0].z - s[1].z,
			vxs(x3, y3, x4, y4), y3 - y4) /
			vxs(s[0].x - s[1].x, s[0].z - s[1].z, x3 - x4, y3 - y4);
	return (xy);
}

/* If it's partially behind the player, clip it against player's view frustrum */
void	player_view_fustrum(t_doom *doom, t_xyz viewed_sectors[2])
{
	t_xyz i1;
	t_xyz i2;

	t_xyz org1 = (t_xyz){.x = viewed_sectors[0].x, .y = 0, .z = viewed_sectors[0].z};
	t_xyz org2 = (t_xyz){.x = viewed_sectors[1].x, .y = 0, .z = viewed_sectors[1].z};
	i1 = intersect(viewed_sectors, -NEARSIDE, NEARZ, -FARSIDE, FARZ);
	i2 = intersect(viewed_sectors, NEARSIDE, NEARZ, FARSIDE, FARZ);
	if (viewed_sectors[0].z < NEARZ)
	{
		if (i1.y > 0)
			viewed_sectors[0] = (t_xyz){.x = i1.x, .z = i1.y};
		else
			viewed_sectors[0] = (t_xyz){.x = i2.x, .z = i2.y};
	}
	if (viewed_sectors[1].z < NEARZ)
	{
		if (i1.y > 0)
			viewed_sectors[1] = (t_xyz){.x = i1.x, .z = i1.y};
		else
			viewed_sectors[1] = (t_xyz){.x = i2.x, .z = i2.y};
	}
	//Cut the texture if smaller wall smaller than texture
	if (fabsf(viewed_sectors[1].x - viewed_sectors[0].x) > fabsf(viewed_sectors[1].z - viewed_sectors[0].z))
	{
		doom->u0 = (viewed_sectors[0].x - org1.x) * doom->u1 / (org2.x - org1.x);
		doom->u1 = (viewed_sectors[1].x - org1.x) * doom->u1 / (org2.x - org1.x);
	}
	else
	{
		doom->u0 = (viewed_sectors[0].z - org1.z) * doom->u1 / (org2.z - org1.z);
		doom->u1 = (viewed_sectors[1].z - org1.z) * doom->u1 / (org2.z - org1.z);
	}
}
