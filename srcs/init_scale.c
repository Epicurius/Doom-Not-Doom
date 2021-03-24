
#include "doom.h"

void	init_wsprite_scale(t_doom *doom, t_wall *wall)
{
	int i;
	t_sprite *wsprite;

	i = -1;
	while (++i < wall->wsprite.total)
	{
		wsprite = &wall->wsprite.num[i];
		wsprite->scale_h = wsprite->scale_w * doom->textures[wsprite->tx].ratio;
		wsprite->scale_w = (doom->textures[wsprite->tx].w / wsprite->scale_w)
					* wall->width;
		wsprite->scale_h = (doom->textures[wsprite->tx].h / wsprite->scale_h)
					* wall->height;
		//printf("%f %f\n", wsprite->scale_w, wsprite->scale_h);
	}

}

void	init_scale(t_doom *doom)
{
	int i;
	int j;
	t_wall *wall;

	i = -1;
	while (++i < doom->nb.walls)
	{
		wall = &doom->walls[i];
		wall->width = point_distance_2d(wall->v1.x, wall->v1.y, wall->v2.x, wall->v2.y);
		wall->height = (doom->sectors[wall->sect].ceiling.y - doom->sectors[wall->sect].floor.y);
		wall->scale_w = (doom->textures[wall->wtx].w / wall->scale) * wall->width;
		wall->scale_h = (doom->textures[wall->wtx].h / wall->scale) * wall->height;
		init_wsprite_scale(doom, wall);
	}
}
