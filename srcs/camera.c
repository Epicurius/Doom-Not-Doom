/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:42:15 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/01 11:56:28 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//void	set_camera(t_doom *doom)
//{
//	double		vfov;
//	double		hfov;
//	
//	hfov = doom->settings.fov;
//	vfov = (180.0 / M_PI) * atan(tan((CONVERT_TO_RADIANS
//		* hfov / 2)) / (doom->surface->w / (double)doom->surface->h)) * 2;
//	double near_down = tan(CONVERT_TO_RADIANS * vfov / 2) * NEAR_Z;
//	double y2 = (near_down / NEAR_Z);
//	double vscale = (doom->surface->h / 2.0) / y2;
//	printf("%f\n", vscale);
//}

/*
 *	Inits the camera, FOV, view fustrum and view scale.
 */
void	init_camera(t_doom *doom)
{
	double		vfov;
	double		hfov;
	t_camera	*cam;

	cam = &doom->cam;
	hfov = tan(CONVERT_TO_RADIANS * doom->settings.fov * 0.5);
	cam->near_left = -hfov * NEAR_Z;
	cam->near_right = hfov * NEAR_Z;
	cam->far_left = -hfov * FAR_Z;
	cam->far_right = hfov * FAR_Z;
	cam->range = cam->near_right - cam->near_left;
	vfov = atan(hfov / (doom->surface->w / (double)doom->surface->h))
		* (180.0 / M_PI);
	cam->scale = (doom->surface->h / 2) / tan(CONVERT_TO_RADIANS * vfov);

	//cam->scale = (float)doom->surface->h / (2 * tan(0.5 * doom->settings.fov * M_PI / 180.0));
	//ft_printf("%f\n", cam->scale);
	//set_camera(doom);
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
