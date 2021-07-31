/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:08:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/31 10:09:21 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	curr_floor_and_ceil(t_doom *doom, t_wall *w)
{
	t_fc		v1;
	t_fc		v2;
	double		eye_z;

	eye_z = doom->player.where.z + doom->player.eyelvl;
	v1.floor = doom->sectors[w->sect].floor.y - eye_z;
	v2.floor = doom->sectors[w->sect].floor.y - eye_z;
	v1.ceiling = doom->sectors[w->sect].ceiling.y - eye_z;
	v2.ceiling = doom->sectors[w->sect].ceiling.y - eye_z;
	w->static_v1.floor = doom->c.y + (v1.floor + w->angle_z1) * w->scale_v1;
	w->static_v1.ceiling = doom->c.y + (v1.ceiling + w->angle_z1) * w->scale_v1;
	w->static_v2.floor = doom->c.y + (v2.floor + w->angle_z2) * w->scale_v2;
	w->static_v2.ceiling = doom->c.y + (v2.ceiling + w->angle_z2) * w->scale_v2;
	w->static_range.floor = w->static_v2.floor - w->static_v1.floor;
	w->static_range.ceiling = w->static_v2.ceiling - w->static_v1.ceiling;
}

static void	slope_curr_floor_and_ceil(t_doom *doom, t_wall *w, t_v3 p1, t_v3 p2)
{
	t_fc		v1;
	t_fc		v2;
	double		eye_z;

	eye_z = doom->player.where.z + doom->player.eyelvl;
	v1.floor = floor_at(&doom->sectors[w->sect], p1) - eye_z;
	v1.ceiling = ceiling_at(&doom->sectors[w->sect], p1) - eye_z;
	v2.floor = floor_at(&doom->sectors[w->sect], p2) - eye_z;
	v2.ceiling = ceiling_at(&doom->sectors[w->sect], p2) - eye_z;
	w->slope_v1.floor = doom->c.y + (v1.floor + w->angle_z1) * w->scale_v1;
	w->slope_v1.ceiling = doom->c.y + (v1.ceiling + w->angle_z1) * w->scale_v1;
	w->slope_v2.floor = doom->c.y + (v2.floor + w->angle_z2) * w->scale_v2;
	w->slope_v2.ceiling = doom->c.y + (v2.ceiling + w->angle_z2) * w->scale_v2;
	w->slope_range.floor = w->slope_v2.floor - w->slope_v1.floor;
	w->slope_range.ceiling = w->slope_v2.ceiling - w->slope_v1.ceiling;
}

//		screen y for floor and ceiling vertex
//		z of floor and ceiling with slope
static void	neighbour_floor_and_ceil(t_doom *doom, t_wall *w, t_v3 p1, t_v3 p2)
{
	t_fc		v1;
	t_fc		v2;
	double		eye_z;

	eye_z = doom->player.where.z + doom->player.eyelvl;
	v1.floor = floor_at(&doom->sectors[w->n], p1) - eye_z;
	v1.ceiling = ceiling_at(&doom->sectors[w->n], p1) - eye_z;
	v2.floor = floor_at(&doom->sectors[w->n], p2) - eye_z;
	v2.ceiling = ceiling_at(&doom->sectors[w->n], p2) - eye_z;
	w->nslope_v1.floor = doom->c.y + (v1.floor + w->angle_z1) * w->scale_v1;
	w->nslope_v1.ceiling = doom->c.y + (v1.ceiling + w->angle_z1) * w->scale_v1;
	w->nslope_v2.floor = doom->c.y + (v2.floor + w->angle_z2) * w->scale_v2;
	w->nslope_v2.ceiling = doom->c.y + (v2.ceiling + w->angle_z2) * w->scale_v2;
	w->nslope_range.floor = w->nslope_v2.floor - w->nslope_v1.floor;
	w->nslope_range.ceiling = w->nslope_v2.ceiling - w->nslope_v1.ceiling;
}

static void	vertex_relative_pos(t_doom *doom, t_wall *wall, t_v3 *p1, t_v3 *p2)
{
	t_player	*p;

	p = &doom->player;
	p1->x = wall->cv1.x * p->anglesin + wall->cv1.z * p->anglecos + p->where.x;
	p1->y = wall->cv1.z * p->anglesin - wall->cv1.x * p->anglecos + p->where.y;
	p2->x = wall->cv2.x * p->anglesin + wall->cv2.z * p->anglecos + p->where.x;
	p2->y = wall->cv2.z * p->anglesin - wall->cv2.x * p->anglecos + p->where.y;
}

/* Do perspective transformation */
void	project_wall(t_doom *doom, t_wall *wall)
{
	t_v3		p1;
	t_v3		p2;

	wall->scale_v1 = doom->cam.scale / -wall->cv1.z;
	wall->scale_v2 = doom->cam.scale / -wall->cv2.z;
	wall->cx1 = doom->c.x + (wall->cv1.x * wall->scale_v1);
	wall->cx2 = doom->c.x + (wall->cv2.x * wall->scale_v2);
	wall->x1 = doom->c.x + wall->sv1.x * doom->cam.scale / -wall->sv1.z;
	wall->x2 = doom->c.x + wall->sv2.x * doom->cam.scale / -wall->sv2.z;
	wall->xrange = wall->x2 - wall->x1;
	wall->zrange = wall->sv1.z - wall->sv2.z;
	wall->zcomb = wall->sv2.z * wall->sv1.z;
	wall->x0z1 = wall->v1.x * wall->sv2.z;
	wall->x1z0 = wall->v2.x * wall->sv1.z;
	wall->xzrange = wall->x1z0 - wall->x0z1;
	wall->y0z1 = wall->v1.y * wall->sv2.z;
	wall->y1z0 = wall->v2.y * wall->sv1.z;
	wall->yzrange = wall->y1z0 - wall->y0z1;
	wall->angle_z1 = wall->cv1.z * doom->player.pitch;
	wall->angle_z2 = wall->cv2.z * doom->player.pitch;
	curr_floor_and_ceil(doom, wall);
	vertex_relative_pos(doom, wall, &p1, &p2);
	slope_curr_floor_and_ceil(doom, wall, p1, p2);
	if (wall->n != -1)
		neighbour_floor_and_ceil(doom, wall, p1, p2);
}
