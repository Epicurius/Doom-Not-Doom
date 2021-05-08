/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_perspective.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:08:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/05 11:39:42 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		project_wall(t_doom *doom, t_wall *wall)
{
	t_camera cam;

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
	t_sector *sector;

	sector = &doom->sectors[wall->sect];
	wall->angle_z1 = wall->cv1.z * doom->player.pitch;
	wall->angle_z2 = wall->cv2.z * doom->player.pitch;

	double yfloor = sector->floor.correct;
	double yceil = sector->ceiling.correct;
	wall->s1.ceiling = doom->h2 + (yceil  + wall->angle_z1) * wall->scale_v1;
	wall->s2.ceiling = doom->h2 + (yceil  + wall->angle_z2) * wall->scale_v2;
	wall->s1.floor = doom->h2 + (yfloor + wall->angle_z1) * wall->scale_v1;
	wall->s2.floor = doom->h2 + (yfloor + wall->angle_z2) * wall->scale_v2;
	wall->range.floor = wall->s2.floor - wall->s1.floor;
	wall->range.ceiling = wall->s2.ceiling - wall->s1.ceiling;

	if (wall->n == -1)
		return ;

	double nyfloor = doom->sectors[wall->n].floor.correct;
	double nyceil = doom->sectors[wall->n].ceiling.correct;
	wall->s1_n.ceiling = doom->h2 + (nyceil  + wall->angle_z1) * wall->scale_v1;
	wall->s2_n.ceiling = doom->h2 + (nyceil  + wall->angle_z2) * wall->scale_v2;
	wall->s1_n.floor = doom->h2 + (nyfloor + wall->angle_z1) * wall->scale_v1;
	wall->s2_n.floor = doom->h2 + (nyfloor + wall->angle_z2) * wall->scale_v2;
	wall->range_n.floor = wall->s2_n.floor - wall->s1_n.floor;
	wall->range_n.ceiling = wall->s2_n.ceiling - wall->s1_n.ceiling;
}
