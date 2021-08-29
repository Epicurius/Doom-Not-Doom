/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:42:15 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/29 10:56:45 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Inits the camera, FOV, view fustrum and view scale.
 */
void	init_camera(t_doom *doom)
{
	double		vfov;
	double		hfov;
	t_camera	*cam;

	cam = &doom->cam;
	hfov = doom->settings.fov;
	cam->near_left = -tan(CONVERT_TO_RADIANS * hfov * 0.5) * NEAR_Z;
	cam->near_right = tan(CONVERT_TO_RADIANS * hfov * 0.5) * NEAR_Z;
	cam->far_left = -tan(CONVERT_TO_RADIANS * hfov * 0.5) * FAR_Z;
	cam->far_right = tan(CONVERT_TO_RADIANS * hfov * 0.5) * FAR_Z;
	cam->range = cam->near_right - cam->near_left;
	vfov = atan(tan((CONVERT_TO_RADIANS * hfov * 0.5))
			/ (doom->settings.size.x / (double)doom->settings.size.y))
		* (180.0 / M_PI) * 2;
	cam->scale = doom->c.y / tan(CONVERT_TO_RADIANS * vfov * 0.5);
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
	doom->player.anglesin = sin(doom->player.yaw);
	doom->player.anglecos = cos(doom->player.yaw);
	doom->player.horizon = doom->c.y - doom->player.pitch * doom->cam.scale;
}
