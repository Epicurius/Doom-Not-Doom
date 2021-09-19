/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:08:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/19 13:11:00 by nneronin         ###   ########.fr       */
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
	v1.floor = doom->sectors[w->sect].floor.height - eye_z;
	v2.floor = doom->sectors[w->sect].floor.height - eye_z;
	v1.ceiling = doom->sectors[w->sect].ceiling.height - eye_z;
	v2.ceiling = doom->sectors[w->sect].ceiling.height - eye_z;
	w->stat_y1.floor = doom->c.y + (v1.floor + w->pitch_z1) * w->fov_z1;
	w->stat_y1.ceiling = doom->c.y + (v1.ceiling + w->pitch_z1) * w->fov_z1;
	w->stat_y2.floor = doom->c.y + (v2.floor + w->pitch_z2) * w->fov_z2;
	w->stat_y2.ceiling = doom->c.y + (v2.ceiling + w->pitch_z2) * w->fov_z2;
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

	eye_z = doom->player.where.z + doom->player.eyelvl;
	v1.floor = floor_at(&doom->sectors[w->sect], p1) - eye_z;
	v1.ceiling = ceiling_at(&doom->sectors[w->sect], p1) - eye_z;
	v2.floor = floor_at(&doom->sectors[w->sect], p2) - eye_z;
	v2.ceiling = ceiling_at(&doom->sectors[w->sect], p2) - eye_z;
	w->incl_y1.floor = doom->c.y + (v1.floor + w->pitch_z1) * w->fov_z1;
	w->incl_y1.ceiling = doom->c.y + (v1.ceiling + w->pitch_z1) * w->fov_z1;
	w->incl_y2.floor = doom->c.y + (v2.floor + w->pitch_z2) * w->fov_z2;
	w->incl_y2.ceiling = doom->c.y + (v2.ceiling + w->pitch_z2) * w->fov_z2;
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
	w->incl_ny1.floor = doom->c.y + (v1.floor + w->pitch_z1) * w->fov_z1;
	w->incl_ny1.ceiling = doom->c.y + (v1.ceiling + w->pitch_z1) * w->fov_z1;
	w->incl_ny2.floor = doom->c.y + (v2.floor + w->pitch_z2) * w->fov_z2;
	w->incl_ny2.ceiling = doom->c.y + (v2.ceiling + w->pitch_z2) * w->fov_z2;
	w->incl_nrange.floor = w->incl_ny2.floor - w->incl_ny1.floor;
	w->incl_nrange.ceiling = w->incl_ny2.ceiling - w->incl_ny1.ceiling;
}

/*
 *	Preforms perspective transformation
 */
void	project_wall(t_doom *doom, t_wall *wall)
{
	t_v3		p1;
	t_v3		p2;

	wall->fov_z1 = doom->cam.scale / -wall->cv1.z;
	wall->fov_z2 = doom->cam.scale / -wall->cv2.z;
	wall->pitch_z1 = doom->player.pitch * wall->cv1.z;
	wall->pitch_z2 = doom->player.pitch * wall->cv2.z;
	wall->x1 = wall->sv1.x * doom->cam.scale / -wall->sv1.z + doom->c.x;
	wall->x2 = wall->sv2.x * doom->cam.scale / -wall->sv2.z + doom->c.x;
	wall->cx1 = wall->cv1.x * wall->fov_z1 + doom->c.x;
	wall->cx2 = wall->cv2.x * wall->fov_z2 + doom->c.x;
	wall->xrange = wall->x2 - wall->x1;
	wall->zrange = wall->sv1.z - wall->sv2.z;
	wall->zcomb = wall->sv2.z * wall->sv1.z;
	wall->x1z2 = wall->v1.x * wall->sv2.z;
	wall->y1z2 = wall->v1.y * wall->sv2.z;
	wall->xzrange = wall->v2.x * wall->sv1.z - wall->x1z2;
	wall->yzrange = wall->v2.y * wall->sv1.z - wall->y1z2;
	curr_floor_and_ceiling(doom, wall);
	screen_to_map_vertex(doom->player, &wall->cv1, &p1);
	screen_to_map_vertex(doom->player, &wall->cv2, &p2);
	curr_floor_and_ceil_incl(doom, wall, p1, p2);
	if (wall->n != -1)
		neighbour_floor_and_ceil(doom, wall, p1, p2);
}
