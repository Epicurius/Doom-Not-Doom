/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:42:15 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/26 13:31:33 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//cam->hscale = doom->c.x / (cam->near_up / cam->near_z);
//cam->vscale = doom->c.y / (cam->near_down / cam->near_z);
void	init_camera(t_doom *doom)
{
	t_camera	*cam;

	cam = &doom->cam;
	cam->hfov = doom->settings.fov;
	cam->vfov = (180.0 / M_PI)
		* atan(tan((CONVERT_RADIANS * cam->hfov / 2)) / CAMERA_RATIO) * 2;
	cam->near_z = NEAR_Z;
	cam->far_z = FAR_Z;
	cam->near_left = -tan(CONVERT_RADIANS * cam->hfov / 2) * cam->near_z;
	cam->near_right = tan(CONVERT_RADIANS * cam->hfov / 2) * cam->near_z;
	cam->far_left = -tan(CONVERT_RADIANS * cam->hfov / 2) * cam->far_z;
	cam->far_right = tan(CONVERT_RADIANS * cam->hfov / 2) * cam->far_z;
	cam->near_up = -tan(CONVERT_RADIANS * cam->vfov / 2) * cam->near_z;
	cam->near_down = tan(CONVERT_RADIANS * cam->vfov / 2) * cam->near_z;
	cam->range = cam->near_right - cam->near_left;
	cam->scale = doom->c.y / (cam->near_down / cam->near_z);
	update_camera(doom, 10, 10);
}

void	update_camera(t_doom *doom, int x, int y)
{
	doom->player.yaw *= CONVERT_RADIANS;
	doom->player.yaw += x * doom->settings.mouse.x;
	doom->player.pitch = ft_fclamp(doom->player.pitch + y
			* doom->settings.mouse.y, -1.5, 1.5);
	doom->player.horizon = doom->c.y - doom->player.pitch * doom->cam.scale;
	doom->player.anglesin = sin(doom->player.yaw);
	doom->player.anglecos = cos(doom->player.yaw);
	doom->player.yaw *= CONVERT_DEGREES;
	while (doom->player.yaw > 360)
		doom->player.yaw -= 360;
	while (doom->player.yaw < 0)
		doom->player.yaw += 360;
}
