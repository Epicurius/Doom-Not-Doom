/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:25 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 08:58:38 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

int	clip_wall(t_camera cam, t_wall *wall)
{
	if ((wall->sv1.z < NEAR_Z && wall->sv2.z < NEAR_Z)
		|| (wall->sv1.z > FAR_Z && wall->sv2.z > FAR_Z)
		|| (wall->sv1.z < cam.far_left && wall->sv2.z < cam.far_left)
		|| (wall->sv1.z > cam.far_right && wall->sv2.z > cam.far_right))
		wall->visible = 0;
	else
	{
		wall->visible = 1;
		clip_to_fustrum(cam, wall);
	}
	return (0);
}

void	precompute_texture(t_doom *doom, t_wall *wall)
{
	int	i;

	wall->tscale = new_v2(wall->scale_w / wall->cv2.z, wall->scale_h);
	if (wall->sv2.z)
		wall->tscale.x = wall->scale_w / wall->sv2.z;
	i = -1;
	while (++i < wall->bullet_hole.total)
	{
		wall->bullet_hole.num[i].tscale.x = 128 * wall->width / wall->sv2.z;
		wall->bullet_hole.num[i].tscale.y = 128 * wall->height;
		wall->bullet_hole.num[i].ready = 1;
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
		wall->wsprite.num[i].ready = 1;
	}
}

void	precompute_floor_ceil(t_doom *doom, t_sector *sector)
{
	double	eye_z;

	eye_z = doom->player.where.z + doom->player.eyelvl;
	sector->floor.feet = doom->c.y + (floor_at(sector, doom->player.where)
			- eye_z + NEAR_Z * doom->player.pitch) * doom->cam.scale / -NEAR_Z;
	sector->ceiling.head = doom->c.y + (ceiling_at(sector, doom->player.where)
			- eye_z + NEAR_Z * doom->player.pitch) * doom->cam.scale / -NEAR_Z;
}

void	precompute_walls(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		doom->sectors[i].visible = 0;
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
