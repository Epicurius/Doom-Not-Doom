
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
	update_camera(doom, 0, 0);
}

void	update_camera(t_doom *doom, int x, int y)
{
	//printf("Yaw %f\n", doom->player.yaw);
	doom->player.yaw *= CONVERT_RADIANS;
	doom->player.yaw += x * MOUSE_X;
	//radians_fix(&doom->player.yaw);
	doom->player.pitch = clamp(doom->player.pitch + y * MOUSE_Y, -2, 2);
	doom->player.horizon = doom->h2 - PLAYER.pitch * doom->cam.scale;
	doom->player.anglesin = sin(doom->player.yaw);
	doom->player.anglecos = cos(doom->player.yaw);
	doom->player.yaw *= CONVERT_DEGREES;
	while (doom->player.yaw > 360)
		doom->player.yaw -= 360;
	while (doom->player.yaw < 0)
		doom->player.yaw += 360;
}
