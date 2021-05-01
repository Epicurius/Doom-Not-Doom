
#include "doom.h"

void	radians_fix(double *yaw)
{
	*yaw *= CONVERT_DEGREES;
	while (*yaw > 360)
		*yaw -= 360;
	while (*yaw < 0)
		*yaw += 360;
	*yaw *= CONVERT_RADIANS;
}

void	init_camera(t_doom *doom)
{
	t_camera *cam;

	cam = &doom->cam;

	cam->hfov = FOV;
	cam->vfov = (180.0 / M_PI) * atan(tan((CONVERT_RADIANS * cam->hfov / 2)) /
				CAMERA_RATIO) * 2;
	cam->near_z =	NEAR_Z;
	cam->far_z =	FAR_Z;
	cam->near_left = -tan(CONVERT_RADIANS * cam->hfov / 2) * cam->near_z;
	cam->near_right = tan(CONVERT_RADIANS * cam->hfov / 2) * cam->near_z;
	cam->far_left =  -tan(CONVERT_RADIANS * cam->hfov / 2) * cam->far_z;
	cam->far_right =  tan(CONVERT_RADIANS * cam->hfov / 2) * cam->far_z;
	cam->near_up =   -tan(CONVERT_RADIANS * cam->vfov / 2) * cam->near_z;
	cam->near_down =  tan(CONVERT_RADIANS * cam->vfov / 2) * cam->near_z;
	cam->range = cam->near_right - cam->near_left;
	cam->hscale = doom->w2 / (cam->near_up / cam->near_z);
	cam->vscale = doom->h2 / (cam->near_down / cam->near_z);
	cam->scale = cam->vscale;
	update_camera(doom, 10, 10);
}

void	update_camera(t_doom *doom, int x, int y)
{
	doom->player.yaw *= CONVERT_RADIANS;
	doom->player.yaw += x * MOUSE_X;
	doom->player.pitch = ft_clamp(doom->player.pitch + y * MOUSE_Y, -1, 1);
	doom->player.horizon = doom->h2 - doom->player.pitch * doom->cam.scale;
	doom->player.anglesin = sin(doom->player.yaw);
	doom->player.anglecos = cos(doom->player.yaw);
	doom->player.yaw *= CONVERT_DEGREES;
	while (doom->player.yaw > 360)
		doom->player.yaw -= 360;
	while (doom->player.yaw < 0)
		doom->player.yaw += 360;
}
