/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:08:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/18 15:56:07 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Calculate floor and ceiling dimensions.
 */
static void	curr_floor_and_ceiling(t_doom *doom, t_wall *w)
{
	t_fc		v1;
	t_fc		v2;
	TEMP_FLOAT		eye_z;

	eye_z = doom->player.where.z + doom->player.eyelvl;
	v1.floor = doom->sectors[w->sect].floor.y - eye_z;
	v2.floor = doom->sectors[w->sect].floor.y - eye_z;
	v1.ceiling = doom->sectors[w->sect].ceiling.y - eye_z;
	v2.ceiling = doom->sectors[w->sect].ceiling.y - eye_z;
	w->stat_y1.floor = doom->c.y + (v1.floor + w->angle_z1) * w->fov_scale_1;
	w->stat_y1.ceiling = doom->c.y + (v1.ceiling + w->angle_z1) * w->fov_scale_1;
	w->stat_y2.floor = doom->c.y + (v2.floor + w->angle_z2) * w->fov_scale_2;
	w->stat_y2.ceiling = doom->c.y + (v2.ceiling + w->angle_z2) * w->fov_scale_2;
	w->stat_range.floor = w->stat_y2.floor - w->stat_y1.floor;
	w->stat_range.ceiling = w->stat_y2.ceiling - w->stat_y1.ceiling;
}

/*
 *	Calculate sloping floor and ceiling dimensions.
 */
static void	curr_floor_and_ceil_incl(t_doom *doom, t_wall *w, t_v3 p1, t_v3 p2)
{
	t_fc		v1;
	t_fc		v2;
	TEMP_FLOAT		eye_z;

	//if (!doom->sectors[w->sect].floor_slope && !doom->sectors[w->sect].ceiling_slope)
	//	return ;
	eye_z = doom->player.where.z + doom->player.eyelvl;
	v1.floor = floor_at(&doom->sectors[w->sect], p1) - eye_z;
	v1.ceiling = ceiling_at(&doom->sectors[w->sect], p1) - eye_z;
	v2.floor = floor_at(&doom->sectors[w->sect], p2) - eye_z;
	v2.ceiling = ceiling_at(&doom->sectors[w->sect], p2) - eye_z;
	w->incl_y1.floor = doom->c.y + (v1.floor + w->angle_z1) * w->fov_scale_1;
	w->incl_y1.ceiling = doom->c.y + (v1.ceiling + w->angle_z1) * w->fov_scale_1;
	w->incl_y2.floor = doom->c.y + (v2.floor + w->angle_z2) * w->fov_scale_2;
	w->incl_y2.ceiling = doom->c.y + (v2.ceiling + w->angle_z2) * w->fov_scale_2;
	w->incl_range.floor = w->incl_y2.floor - w->incl_y1.floor;
	w->incl_range.ceiling = w->incl_y2.ceiling - w->incl_y1.ceiling;
}

/*
 *	Calculate neighbour floor and ceiling dimensions.
 *	Screen y for floor and ceiling vertex, z of floor and ceiling with slope.
 */
static void	neighbour_floor_and_ceil(t_doom *doom, t_wall *w, t_v3 p1, t_v3 p2)
{
	t_fc		v1;
	t_fc		v2;
	TEMP_FLOAT		eye_z;

	eye_z = doom->player.where.z + doom->player.eyelvl;
	v1.floor = floor_at(&doom->sectors[w->n], p1) - eye_z;
	v1.ceiling = ceiling_at(&doom->sectors[w->n], p1) - eye_z;
	v2.floor = floor_at(&doom->sectors[w->n], p2) - eye_z;
	v2.ceiling = ceiling_at(&doom->sectors[w->n], p2) - eye_z;
	w->incl_ny1.floor = doom->c.y + (v1.floor + w->angle_z1) * w->fov_scale_1;
	w->incl_ny1.ceiling = doom->c.y + (v1.ceiling + w->angle_z1) * w->fov_scale_1;
	w->incl_ny2.floor = doom->c.y + (v2.floor + w->angle_z2) * w->fov_scale_2;
	w->incl_ny2.ceiling = doom->c.y + (v2.ceiling + w->angle_z2) * w->fov_scale_2;
	w->incl_nrange.floor = w->incl_ny2.floor - w->incl_ny1.floor;
	w->incl_nrange.ceiling = w->incl_ny2.ceiling - w->incl_ny1.ceiling;
}

/*
 *	Transforms screen coordinates of v1, v2 to real space coordinates.
 */
static void	vertex_relative_pos(t_doom *doom, t_wall *wall, t_v3 *p1, t_v3 *p2)
{
	t_player	*p;

	p = &doom->player;
	p1->x = wall->cv1.x * p->anglesin + wall->cv1.z * p->anglecos + p->where.x;
	p1->y = wall->cv1.z * p->anglesin - wall->cv1.x * p->anglecos + p->where.y;
	p2->x = wall->cv2.x * p->anglesin + wall->cv2.z * p->anglecos + p->where.x;
	p2->y = wall->cv2.z * p->anglesin - wall->cv2.x * p->anglecos + p->where.y;
}

/*
 *	Preforms perspective transformation
 */
void	project_wall(t_doom *doom, t_wall *wall)
{
	t_v3		p1;
	t_v3		p2;

	wall->fov_scale_1 = doom->cam.scale / -wall->cv1.z;
	wall->fov_scale_2 = doom->cam.scale / -wall->cv2.z;
	
	wall->x1 = wall->sv1.x * doom->cam.scale / -wall->sv1.z + doom->c.x;
	wall->x2 = wall->sv2.x * doom->cam.scale / -wall->sv2.z + doom->c.x;
	wall->cx1 = wall->cv1.x * wall->fov_scale_1 + doom->c.x;
	wall->cx2 = wall->cv2.x * wall->fov_scale_2 + doom->c.x;

	wall->xrange = wall->x2 - wall->x1;
	wall->zrange = wall->sv1.z - wall->sv2.z;
	wall->zcomb = wall->sv2.z * wall->sv1.z;
	wall->x1z2 = wall->v1.x * wall->sv2.z;
	wall->xzrange = wall->v2.x * wall->sv1.z - wall->x1z2;
	wall->y1z2 = wall->v1.y * wall->sv2.z;
	wall->yzrange = wall->v2.y * wall->sv1.z - wall->y1z2;
	wall->angle_z1 = wall->cv1.z * doom->player.pitch;
	wall->angle_z2 = wall->cv2.z * doom->player.pitch;
	curr_floor_and_ceiling(doom, wall);
	vertex_relative_pos(doom, wall, &p1, &p2);
	curr_floor_and_ceil_incl(doom, wall, p1, p2);
	if (wall->n != -1)
		neighbour_floor_and_ceil(doom, wall, p1, p2);
}
