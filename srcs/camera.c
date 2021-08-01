/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:42:15 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 08:00:19 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fix_degrees(double *angle)
{
	*angle *= CONVERT_TO_DEGREES;
	while (*angle > 360)
		*angle -= 360;
	while (*angle < 0)
		*angle += 360;
	*angle *= CONVERT_TO_RADIANS;
}

//cam->hscale = doom->c.x / (cam->near_up / cam->near_z);
//cam->vscale = doom->c.y / (cam->near_down / cam->near_z);
void	init_camera(t_doom *doom)
{
	t_camera	*cam;

	cam = &doom->cam;
	cam->hfov = doom->settings.fov;
	cam->vfov = atan(tan((CONVERT_TO_RADIANS * cam->hfov / 2)) / CAMERA_RATIO)
		* (180.0 / M_PI) * 2;
	cam->near_z = NEAR_Z;
	cam->far_z = FAR_Z;
	cam->near_left = -tan(CONVERT_TO_RADIANS * cam->hfov / 2) * cam->near_z;
	cam->near_right = tan(CONVERT_TO_RADIANS * cam->hfov / 2) * cam->near_z;
	cam->far_left = -tan(CONVERT_TO_RADIANS * cam->hfov / 2) * cam->far_z;
	cam->far_right = tan(CONVERT_TO_RADIANS * cam->hfov / 2) * cam->far_z;
	cam->near_up = -tan(CONVERT_TO_RADIANS * cam->vfov / 2) * cam->near_z;
	cam->near_down = tan(CONVERT_TO_RADIANS * cam->vfov / 2) * cam->near_z;
	cam->range = cam->near_right - cam->near_left;
	cam->scale = doom->c.y / (cam->near_down / cam->near_z);
	update_camera(doom);
}

void	update_camera(t_doom *doom)
{
	int x;
	int y;
	
	SDL_GetRelativeMouseState(&x, &y);	
	doom->player.yaw += x * doom->settings.mouse.x;
	fix_degrees(&doom->player.yaw);
	doom->player.pitch += y * doom->settings.mouse.y;
	doom->player.pitch = ft_fclamp(doom->player.pitch, -1, 1.5);
	doom->player.horizon = doom->c.y - doom->player.pitch * doom->cam.scale;
	doom->player.anglesin = sin(doom->player.yaw);
	doom->player.anglecos = cos(doom->player.yaw);

}
