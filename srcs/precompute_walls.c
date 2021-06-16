/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:25 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/16 16:21:05 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	clip_to_fustrum(t_camera cam, t_wall *wall)
{
	t_v3 i;

	i = get_intersection(	xyz(wall->sv1.x, wall->sv1.z, 0),
				xyz(wall->sv2.x, wall->sv2.z, 0),
				xyz(cam.near_left, cam.near_z, 0),
				xyz(cam.near_right, cam.near_z, 0));
	if (wall->sv1.z < cam.near_z)
		wall->cv1 = xyz(i.x, 0, i.y);
	else
		wall->cv1 = xyz(wall->sv1.x, 0, wall->sv1.z);
	if (wall->sv2.z < cam.near_z)
		wall->cv2 = xyz(i.x, 0, i.y);
	else
		wall->cv2 = xyz(wall->sv2.x, 0, wall->sv2.z);
}

int	clip_wall(t_camera cam, t_wall *wall)
{
	if ((wall->sv1.z < cam.near_z && wall->sv2.z < cam.near_z) ||
		(wall->sv1.z > cam.far_z && wall->sv2.z > cam.far_z) ||
		(wall->sv1.z < cam.far_left && wall->sv2.z < cam.far_left) ||
		(wall->sv1.z > cam.far_right && wall->sv2.z > cam.far_right))
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
	int i;
	
	if (wall->sv2.z)
		wall->tscale.x = wall->scale_w / wall->sv2.z;
	else
		wall->tscale.x = wall->scale_w / wall->cv2.z;
	wall->tscale.y = wall->scale_h;
	i = -1;
	while (++i < wall->bh.total)
	{
		wall->bh.num[i].tscale.x = 128 * wall->width / wall->sv2.z;
		wall->bh.num[i].tscale.y = 128 * wall->height;
		wall->bh.num[i].ready = 1;
	}
	i = -1;
	while (++i < wall->wsprite.total)
	{
		if (wall->wsprite.num[i].tx == 4)
			clock_wsprite(doom, wall, i);
		else if (wall->wsprite.num[i].tx == 1)
			animate_wsprite(doom, &wall->wsprite.num[i]);
		wall->wsprite.num[i].tscale.x = wall->wsprite.num[i].scale_w / wall->sv2.z;
		wall->wsprite.num[i].tscale.y = wall->wsprite.num[i].scale_h;
		wall->wsprite.num[i].ready = 1;
	}
}

void	precompute_floor_ceil(t_doom *doom, t_sector *sector)
{
	double eye_z;

	eye_z = doom->player.where.z + doom->player.eye_lvl;
	sector->floor.feet = doom->h2 + (get_floor_at_pos(sector, doom->player.where)
		- eye_z + doom->cam.near_z * doom->player.pitch)
		* doom->cam.scale / -doom->cam.near_z;	
	sector->ceiling.head = doom->h2 + (get_ceiling_at_pos(sector, doom->player.where)
		- eye_z + doom->cam.near_z * doom->player.pitch)
		* doom->cam.scale / -doom->cam.near_z;
}

void	precompute_walls(t_doom *doom)
{
	int i;

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
