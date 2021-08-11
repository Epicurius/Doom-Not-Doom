/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:42:15 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/11 09:08:53 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Inits the camera, FOV, view fustrum and view scale.
 */
void	init_camera(t_doom *doom)
{
	t_camera	*cam;

	cam = &doom->cam;
	cam->hfov = doom->settings.fov;
	cam->vfov = atan(tan((CONVERT_TO_RADIANS * cam->hfov * 0.5)) / CAMERA_RATIO)
		* (180.0 / M_PI) * 2;
	cam->near_left = -tan(CONVERT_TO_RADIANS * cam->hfov * 0.5) * NEAR_Z;
	cam->near_right = tan(CONVERT_TO_RADIANS * cam->hfov * 0.5) * NEAR_Z;
	cam->far_left = -tan(CONVERT_TO_RADIANS * cam->hfov * 0.5) * FAR_Z;
	cam->far_right = tan(CONVERT_TO_RADIANS * cam->hfov * 0.5) * FAR_Z;
	cam->near_up = -tan(CONVERT_TO_RADIANS * cam->vfov * 0.5) * NEAR_Z;
	cam->near_down = tan(CONVERT_TO_RADIANS * cam->vfov * 0.5) * NEAR_Z;
	cam->range = cam->near_right - cam->near_left;
	cam->scale = doom->c.y / (cam->near_down / NEAR_Z);
	update_camera(doom);
}

/*
 *	Updates camera yaw, pitch according to mouse movement.
 */
void	update_camera(t_doom *doom)
{
	int	x;
	int	y;

	SDL_GetRelativeMouseState(&x, &y);
	doom->player.yaw += x * doom->settings.mouse.x;
	clamp_radians(&doom->player.yaw);
	doom->player.pitch += y * doom->settings.mouse.y;
	doom->player.pitch = ft_fclamp(doom->player.pitch, -1, 1.5);
	doom->player.horizon = doom->c.y - doom->player.pitch * doom->cam.scale;
	doom->player.anglesin = sin(doom->player.yaw);
	doom->player.anglecos = cos(doom->player.yaw);
}
