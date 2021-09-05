/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_skybox.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:20 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/05 07:07:33 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Calculates the skybox box.
 *	Box dimensions 5 from player in each direction(x,y,z)
 *	So a 10x10x10 box.
 */
void	compute_skybox(t_doom *doom)
{
	t_player	player;

	player = doom->player;
	doom->skybox[0].sv1.x = (-5) * player.anglesin - (-5) * player.anglecos;
	doom->skybox[0].sv1.z = (-5) * player.anglecos + (-5) * player.anglesin;
	doom->skybox[1].sv1.x = (5) * player.anglesin - (-5) * player.anglecos;
	doom->skybox[1].sv1.z = (5) * player.anglecos + (-5) * player.anglesin;
	doom->skybox[2].sv1.x = (5) * player.anglesin - (5) * player.anglecos;
	doom->skybox[2].sv1.z = (5) * player.anglecos + (5) * player.anglesin;
	doom->skybox[3].sv1.x = (-5) * player.anglesin - (5) * player.anglecos;
	doom->skybox[3].sv1.z = (-5) * player.anglecos + (5) * player.anglesin;
	doom->skybox[0].sv2 = doom->skybox[1].sv1;
	doom->skybox[1].sv2 = doom->skybox[2].sv1;
	doom->skybox[2].sv2 = doom->skybox[3].sv1;
	doom->skybox[3].sv2 = doom->skybox[0].sv1;
}

/*
 *	Calculates the values for projecting the skybox around the player.
 */
void	project_skybox(t_doom *doom, t_wall *wall)
{
	wall->scale_v1 = doom->cam.scale / -wall->cv1.z;
	wall->scale_v2 = doom->cam.scale / -wall->cv2.z;
	wall->cx1 = doom->c.x + (wall->cv1.x * wall->scale_v1);
	wall->cx2 = doom->c.x + (wall->cv2.x * wall->scale_v2);
	wall->cx1 = ceil(wall->cx1);
	wall->x1 = doom->c.x + wall->sv1.x * doom->cam.scale / -wall->sv1.z;
	wall->x2 = doom->c.x + wall->sv2.x * doom->cam.scale / -wall->sv2.z;
	wall->angle_z1 = wall->cv1.z * doom->player.pitch;
	wall->angle_z2 = wall->cv2.z * doom->player.pitch;
	wall->slope_v1.ceiling = doom->c.y + (5 + wall->angle_z1) * wall->scale_v1;
	wall->slope_v2.ceiling = doom->c.y + (5 + wall->angle_z2) * wall->scale_v2;
	wall->slope_v1.floor = doom->c.y + (-5 + wall->angle_z1) * wall->scale_v1;
	wall->slope_v2.floor = doom->c.y + (-5 + wall->angle_z2) * wall->scale_v2;
	wall->xrange = wall->x2 - wall->x1;
	wall->slope_range.floor = wall->slope_v2.floor - wall->slope_v1.floor;
	wall->slope_range.ceiling = wall->slope_v2.ceiling - wall->slope_v1.ceiling;
	wall->zrange = wall->sv1.z - wall->sv2.z;
	wall->zcomb = wall->sv2.z * wall->sv1.z;
	wall->x0z1 = wall->v1.x * wall->sv2.z;
	wall->x1z0 = wall->v2.x * wall->sv1.z;
	wall->xzrange = wall->x1z0 - wall->x0z1;
	wall->y0z1 = wall->v1.y * wall->sv2.z;
	wall->y1z0 = wall->v2.y * wall->sv1.z;
	wall->yzrange = wall->y1z0 - wall->y0z1;
}

/*
 *	Loops all of the skybox walls and calculates those that intersect with
 *	player view fustrum.
 */
void	precompute_skybox(t_doom *doom)
{
	int	i;

	compute_skybox(doom);
	i = -1;
	while (++i < 4)
	{
		clip_wall(doom->cam, &doom->skybox[i]);
		if (!doom->skybox[i].visible)
			continue ;
		project_skybox(doom, &doom->skybox[i]);
	}
}

/*
 *	Inits skybox vertices,
 *	10x10x10 box.
 */
void	init_skybox(t_doom *doom)
{
	doom->skybox[0].v1 = new_v3(0, 0, 0);
	doom->skybox[1].v1 = new_v3(10, 0, 0);
	doom->skybox[2].v1 = new_v3(10, 10, 0);
	doom->skybox[3].v1 = new_v3(0, 10, 0);
	doom->skybox[0].v2 = doom->skybox[1].v1;
	doom->skybox[1].v2 = doom->skybox[2].v1;
	doom->skybox[2].v2 = doom->skybox[3].v1;
	doom->skybox[3].v2 = doom->skybox[0].v1;
}
