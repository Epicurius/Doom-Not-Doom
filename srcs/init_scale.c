
#include "doom.h"

void	init_wsprite_scale(t_doom *doom, t_wall *wall)
{
	int i;
	int x;
	int y;
	t_sprite *wsprite;

	i = -1;
	while (++i < wall->wsprite.total)
	{
		wsprite = &wall->wsprite.num[i];
		x = doom->mtx[wsprite->tx].w;
		y = doom->mtx[wsprite->tx].h;
		if (wsprite->tx == -1)
			x = doom->clock->w, y = doom->clock->h;
		else if (wsprite->tx == 1)
			x = 64, y = 64;
		wsprite->scale_h = wsprite->scale_w * ((float)y / (float)x);
		wsprite->scale_w = (x / wsprite->scale_w) * wall->width;
		wsprite->scale_h = (y / wsprite->scale_h) * wall->height;
		wsprite->src = new_rect(0, 0, x, y);
	}

}

void	init_scale(t_doom *doom)
{
	int i;
	t_wall *wall;

	i = -1;
	while (++i < doom->nb.walls)
	{
		wall = &doom->walls[i];
		wall->width = point_distance_2d(wall->v1.x, wall->v1.y, wall->v2.x, wall->v2.y);
		wall->height = (doom->sectors[wall->sect].ceiling.y - doom->sectors[wall->sect].floor.y);
		wall->scale_w = (doom->mtx[wall->wtx].w / wall->scale) * wall->width;
		wall->scale_h = (doom->mtx[wall->wtx].h / wall->scale) * wall->height;
		init_wsprite_scale(doom, wall);
	}
}
