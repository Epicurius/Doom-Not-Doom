/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:25 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/18 15:24:05 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Clips walls to player fustrum
 *	(left and right wall that are partially in view)
 */
void	clip_to_fustrum(t_camera cam, t_wall *wall)
{
	t_v3	i;

	i = get_intersection_v2(new_v3(wall->sv1.x, wall->sv1.z, 0),
			new_v3(wall->sv2.x, wall->sv2.z, 0),
			new_v3(cam.near_left, NEAR_Z, 0),
			new_v3(cam.near_right, NEAR_Z, 0));
	if (wall->sv1.z < NEAR_Z)
		wall->cv1 = new_v3(i.x, 0, i.y);
	else
		wall->cv1 = new_v3(wall->sv1.x, 0, wall->sv1.z);
	if (wall->sv2.z < NEAR_Z)
		wall->cv2 = new_v3(i.x, 0, i.y);
	else
		wall->cv2 = new_v3(wall->sv2.x, 0, wall->sv2.z);
}

/*
 *	If wall not in player view wall->visible = 0;
 *	else wall->visible = 1 and clip it to fustrum.
 */
int	clip_wall(t_camera cam, t_wall *wall)
{
	if ((wall->sv1.z < NEAR_Z && wall->sv2.z < NEAR_Z)
		|| (wall->sv1.z > FAR_Z && wall->sv2.z > FAR_Z)
		|| (wall->sv1.z < cam.far_left && wall->sv2.z < cam.far_left)
		|| (wall->sv1.z > cam.far_right && wall->sv2.z > cam.far_right))
		wall->visible = FALSE;
	else
	{
		wall->visible = TRUE;
		clip_to_fustrum(cam, wall);
	}
	return (0);
}

/*
 *	Precomputes some map texture scaling.
 */
void	precompute_texture(t_doom *doom, t_wall *wall)
{
	int	i;

	wall->clip_scale = new_v2(wall->stat_scale.x / wall->cv2.z, wall->stat_scale.y);
	if (wall->sv2.z)
		wall->clip_scale.x = wall->stat_scale.x / wall->sv2.z;
	i = -1;
	while (++i < wall->bullet_hole.total)
	{
		wall->bullet_hole.num[i].tscale.x = 64 * wall->width / wall->sv2.z;
		wall->bullet_hole.num[i].tscale.y = 64 * wall->height;
		wall->bullet_hole.num[i].ready = TRUE;
	}
	i = -1;
	while (++i < wall->wsprite.total)
	{
		if (wall->wsprite.num[i].tx == MAP_TEXTURE_AMOUNT - 1)
			clock_wsprite(doom, wall, i);
		else if (wall->wsprite.num[i].state == LOOP)
			animate_wsprite(doom, &wall->wsprite.num[i]);
		wall->wsprite.num[i].tscale = new_v2(
				wall->wsprite.num[i].scale_w / wall->sv2.z,
				wall->wsprite.num[i].scale_h);
		wall->wsprite.num[i].ready = TRUE;
	}
}

/*
 *	Calculates the hights of floor and ceiling at player postion.
 *	This will lighten the load when drawing.
 */
void	precompute_floor_ceil(t_doom *doom, t_sector *sector)
{
	TEMP_FLOAT	eye_z;

	eye_z = doom->player.where.z + doom->player.eyelvl;
	sector->floor.feet = doom->c.y + (floor_at(sector, doom->player.where)
			- eye_z + NEAR_Z * doom->player.pitch) * doom->cam.scale / -NEAR_Z;
	sector->ceiling.head = doom->c.y + (ceiling_at(sector, doom->player.where)
			- eye_z + NEAR_Z * doom->player.pitch) * doom->cam.scale / -NEAR_Z;
}

/*
 *	Prepares all the walls inside player view fustrum for drawing.
 *	aka values that dont need to be calculated more than once per frame,
 *	to make multithreading possible and faster.
 */
void	precompute_walls(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		doom->sectors[i].visible = FALSE;
		precompute_floor_ceil(doom, &doom->sectors[i]);
	}
	i = -1;
	while (++i < doom->nb.walls)
	{
		wall_to_screen_xz(doom->player, &doom->walls[i]);
		clip_wall(doom->cam, &doom->walls[i]);
		if (!doom->walls[i].visible)
			continue ;
		project_wall(doom, &doom->walls[i]);
		precompute_texture(doom, &doom->walls[i]);
	}
}
