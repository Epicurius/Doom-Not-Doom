
#include "doom.h"

void	compute_skybox(t_doom *doom)
{
	t_player player;

	player = doom->player;
	// (coord - 5)
	doom->skybox[0].sv1.x = (-5) * player.anglesin - (-5) * player.anglecos;
	doom->skybox[0].sv1.z = (-5) * player.anglecos + (-5) * player.anglesin;
	doom->skybox[1].sv1.x = (5) * player.anglesin - (-5) * player.anglecos;
	doom->skybox[1].sv1.z = (5) * player.anglecos + (-5) * player.anglesin;
	doom->skybox[2].sv1.x = (5) * player.anglesin - (5) * player.anglecos;
	doom->skybox[2].sv1.z = (5) * player.anglecos + (5) * player.anglesin;
	doom->skybox[3].sv1.x = (-5) * player.anglesin - (5) * player.anglecos;
	doom->skybox[3].sv1.z = (-5) * player.anglecos + (5) * player.anglesin;
	doom->skybox[0].sv2 = doom->skybox[1].sv1;
	doom->skybox[1].sv2 = doom->skybox[2].sv1;
	doom->skybox[2].sv2 = doom->skybox[3].sv1;
	doom->skybox[3].sv2 = doom->skybox[0].sv1;
}


void		project_skybox(t_doom *doom, t_wall *wall)
{
	t_camera cam;

	cam = doom->cam;
	/* Do perspective transformation */
	wall->scale_v1 = cam.scale / -wall->cv1.z;
	wall->scale_v2 = cam.scale / -wall->cv2.z;
	wall->cx1 = doom->w2 + (wall->cv1.x * wall->scale_v1);
	wall->cx2 = doom->w2 + (wall->cv2.x * wall->scale_v2);
	wall->cx1 = ceil(wall->cx1);
	wall->x1 = doom->w2 + wall->sv1.x * cam.scale / -wall->sv1.z;
	wall->x2 = doom->w2 + wall->sv2.x * cam.scale / -wall->sv2.z;

	/*Y for wall 4 corners*/
	wall->angle_z1 = wall->cv1.z * doom->player.pitch;
	wall->angle_z2 = wall->cv2.z * doom->player.pitch;

	wall->s1.ceiling = doom->h2 + (5 + wall->angle_z1) * wall->scale_v1;
	wall->s2.ceiling = doom->h2 + (5 + wall->angle_z2) * wall->scale_v2;
	wall->s1.floor = doom->h2 + (-5 + wall->angle_z1) * wall->scale_v1;
	wall->s2.floor = doom->h2 + (-5 + wall->angle_z2) * wall->scale_v2;

        wall->xrange		= wall->x2 - wall->x1;
	wall->range.floor	= wall->s2.floor - wall->s1.floor;
	wall->range.ceiling	= wall->s2.ceiling - wall->s1.ceiling;
	wall->zrange		= wall->sv1.z - wall->sv2.z;
        wall->zcomb		= wall->sv2.z * wall->sv1.z;
        wall->x0z1		= wall->v1.x * wall->sv2.z;//
        wall->x1z0		= wall->v2.x * wall->sv1.z;//
        wall->xzrange		= wall->x1z0 - wall->x0z1;
        wall->y0z1		= wall->v1.y * wall->sv2.z;//
	wall->y1z0		= wall->v2.y * wall->sv1.z;//
	wall->yzrange		= wall->y1z0 - wall->y0z1;
}

void	precompute_skybox(t_doom *doom)
{
	int	i;

	compute_skybox(doom);
	i = -1;
	while (++i < 4)
	{
		clip_wall(doom->cam, &doom->skybox[i]);
		if (!doom->skybox[i].visible)
			continue ;
		project_skybox(doom, &doom->skybox[i]);
	}
}

void	init_skybox(t_doom *doom)
{
	doom->skybox[0].v1 = xyz(0, 0, 0);
	doom->skybox[1].v1 = xyz(10, 0, 0);
	doom->skybox[2].v1 = xyz(10, 10, 0);
	doom->skybox[3].v1 = xyz(0, 10, 0);
	doom->skybox[0].v2 = doom->skybox[1].v1;
	doom->skybox[1].v2 = doom->skybox[2].v1;
	doom->skybox[2].v2 = doom->skybox[3].v1;
	doom->skybox[3].v2 = doom->skybox[0].v1;
}