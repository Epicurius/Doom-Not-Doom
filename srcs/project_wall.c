/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:08:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/03 17:43:13 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		project_wall(t_doom *doom, t_wall *wall)
{
	t_camera cam;
	t_sector *sector;

	sector = &doom->sectors[wall->sect];

	cam = doom->cam;

	/* Do perspective transformation */
	wall->scale_v1 = cam.scale / -wall->cv1.z;
	wall->scale_v2 = cam.scale / -wall->cv2.z;
	wall->cx1 = doom->w2 + (wall->cv1.x * wall->scale_v1);
	wall->cx2 = doom->w2 + (wall->cv2.x * wall->scale_v2);
	wall->x1 = doom->w2 + wall->sv1.x * cam.scale / -wall->sv1.z;
	wall->x2 = doom->w2 + wall->sv2.x * cam.scale / -wall->sv2.z;

	wall->xrange	= wall->x2 - wall->x1;
	wall->zrange	= wall->sv1.z - wall->sv2.z;
	wall->zcomb		= wall->sv2.z * wall->sv1.z;
	wall->x0z1		= wall->v1.x * wall->sv2.z;
	wall->x1z0		= wall->v2.x * wall->sv1.z;
	wall->xzrange	= wall->x1z0 - wall->x0z1;
	wall->y0z1		= wall->v1.y * wall->sv2.z;
	wall->y1z0		= wall->v2.y * wall->sv1.z;
	wall->yzrange	= wall->y1z0 - wall->y0z1;

	/*Y for wall 4 corners*/
	wall->angle_z1 = wall->cv1.z * doom->player.pitch;
	wall->angle_z2 = wall->cv2.z * doom->player.pitch;
	
	double eye_z = doom->player.where.z + doom->player.eye_lvl;

	wall->s1.c = doom->h2 + (sector->ceiling.y - eye_z + wall->angle_z1) * wall->scale_v1;
	wall->s1.f = doom->h2 + (sector->floor.y - eye_z + wall->angle_z1) * wall->scale_v1;
	wall->s2.c = doom->h2 + (sector->ceiling.y - eye_z + wall->angle_z2) * wall->scale_v2;
	wall->s2.f = doom->h2 + (sector->floor.y - eye_z + wall->angle_z2) * wall->scale_v2;
	wall->range.f = wall->s2.f - wall->s1.f;
	wall->range.c = wall->s2.c - wall->s1.c;


	t_xyz			p1;
	t_xyz			p2;
	double			f1_h;
	double			c1_h;
	double			f2_h;
	double			c2_h;


	p1.x =	wall->cv1.x * doom->player.anglesin +
			wall->cv1.z * doom->player.anglecos + doom->player.where.x;
	p1.y =	wall->cv1.z * doom->player.anglesin -
			wall->cv1.x * doom->player.anglecos + doom->player.where.y;
	p2.x =	wall->cv2.x * doom->player.anglesin +
			wall->cv2.z * doom->player.anglecos + doom->player.where.x;
	p2.y =	wall->cv2.z * doom->player.anglesin -
			wall->cv2.x * doom->player.anglecos + doom->player.where.y;

	//z of floor and ceiling with slope
	f1_h = get_floor_at_pos(sector, p1);
	c1_h = get_ceiling_at_pos(sector, p1);
	f2_h = get_floor_at_pos(sector, p2);
	c2_h = get_ceiling_at_pos(sector, p2);

	// screen y for floor and ceiling vertex
	wall->s1.floor = doom->h2 + (f1_h - eye_z + wall->angle_z1) * wall->scale_v1;
	wall->s1.ceiling = doom->h2 + (c1_h - eye_z + wall->angle_z1) * wall->scale_v1;
	wall->s2.floor = doom->h2 + (f2_h - eye_z + wall->angle_z2) * wall->scale_v2;
	wall->s2.ceiling = doom->h2 + (c2_h - eye_z + wall->angle_z2) * wall->scale_v2;
	wall->range.floor = wall->s2.floor - wall->s1.floor;
	wall->range.ceiling = wall->s2.ceiling - wall->s1.ceiling;

	if (wall->n == -1)
		return ;

	//z of floor and ceiling with slope
	sector = &doom->sectors[wall->n];
	f1_h = get_floor_at_pos(sector, p1);
	c1_h = get_ceiling_at_pos(sector, p1);
	f2_h = get_floor_at_pos(sector, p2);
	c2_h = get_ceiling_at_pos(sector, p2);

	// screen y for floor and ceiling vertex
	wall->s1_n.floor = doom->h2 + (f1_h - eye_z + wall->angle_z1) * wall->scale_v1;
	wall->s1_n.ceiling = doom->h2 + (c1_h - eye_z + wall->angle_z1) * wall->scale_v1;
	wall->s2_n.floor = doom->h2 + (f2_h - eye_z + wall->angle_z2) * wall->scale_v2;
	wall->s2_n.ceiling = doom->h2 + (c2_h - eye_z + wall->angle_z2) * wall->scale_v2;
	wall->range_n.floor = wall->s2_n.floor - wall->s1_n.floor;
	wall->range_n.ceiling = wall->s2_n.ceiling - wall->s1_n.ceiling;
}
