
#include "doom.h"

void	map_player(t_doom *doom)
{
	t_i2	p[2];
	t_map	map;
	t_player player;

	map = doom->map;
	player = doom->player;
	p[0].x = map.pos_x;
	p[0].y = map.pos_y;
	p[1].x = (player.anglecos * FAR_Z - player.anglesin * doom->cam.far_left) + map.pos_x;
	p[1].y = (player.anglesin * FAR_Z + player.anglecos * doom->cam.far_left) + map.pos_y;
	rect_clamp(map.pos_x, map.pos_y, map.w, map.h, &p[1].x, &p[1].y);
	line(doom->surface, MM_VIEW_COLOR, p);
	p[0].x = map.pos_x;
	p[0].y = map.pos_y;
	p[1].x = (player.anglecos * FAR_Z - player.anglesin * doom->cam.far_right) + map.pos_x;
	p[1].y = (player.anglesin * FAR_Z + player.anglecos * doom->cam.far_right) + map.pos_y;
	rect_clamp(map.pos_x, map.pos_y, map.w, map.h, &p[1].x, &p[1].y);
	line(doom->surface, MM_VIEW_COLOR, p);
}

void	draw_map(t_doom *doom)
{
	int s;
	int w;
	t_i2 p[2];
	t_map map = doom->map;
	t_xyz where = doom->player.where;
	t_sector *sect;

	s = -1;
	while (++s < doom->nb.sectors)
	{
		w = -1;
		sect = &doom->sectors[s];
		while (++w < sect->npoints)
		{
			if (sect->wall[w]->n != -1)
				continue ; 
			p[0].x = doom->w2 + (sect->wall[w]->v1.x - where.x) * MM_SECTORS_SCALE;
			p[0].y = doom->h2 + (sect->wall[w]->v1.y - where.y) * MM_SECTORS_SCALE;
			p[1].x = doom->w2 + (sect->wall[w]->v2.x - where.x) * MM_SECTORS_SCALE;
			p[1].y = doom->h2 + (sect->wall[w]->v2.y - where.y) * MM_SECTORS_SCALE;
			if (cohen_sutherland(&p[0], &p[1], map.min, map.max))
				line(doom->surface, 0xFFFFFFFF, p);		
		}
		
	}
}

void	map_area(t_doom *doom)
{
	int x;
	int y;
	Uint32*	pixels = doom->surface->pixels;
	t_map map = doom->map;


	y = map.min.y - MM_BEZEL_SIZE;
	while (y <= map.max.y + MM_BEZEL_SIZE)
	{
		x = map.min.x - MM_BEZEL_SIZE;
		while (x <= map.max.x + MM_BEZEL_SIZE)
		{
			if (x < map.min.x || x > map.max.x || y < map.min.y || y > map.max.y)
				pixels[y * W + x] = MM_BEZEL_COLOR;
			else if (MM_ALPHA > 0)
				pixels[y * W + x] = blend_alpha(pixels[y * W + x], 0, MM_ALPHA);
			x++;
		}
		y++;
	}
}


void	map(t_doom *doom)
{
	map_area(doom);
	draw_map(doom);
	map_player(doom);
}

void	init_minimap(t_doom *doom)
{
	t_map *map;

	map = &doom->map;
	map->h = doom->surface->h * (float)MM_SCALE;
	map->w = map->h;
	map->min.x = doom->w2 - map->w / 2;
	map->min.y = doom->h2 - map->h / 2;
	map->max.x = doom->w2 + map->w / 2;
	map->max.y = doom->h2 + map->h / 2;
	map->pos_x = doom->w2;
	map->pos_y = doom->h2;
}
