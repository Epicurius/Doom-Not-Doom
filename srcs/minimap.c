/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/27 10:59:56 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	rect_clamp(map.pos_x, map.pos_y, map.size.w, map.size.h, &p[1].x, &p[1].y);
	line(doom->surface, MM_VIEW_COLOR, p);
	p[0].x = map.pos_x;
	p[0].y = map.pos_y;
	p[1].x = (player.anglecos * FAR_Z - player.anglesin * doom->cam.far_right) + map.pos_x;
	p[1].y = (player.anglesin * FAR_Z + player.anglecos * doom->cam.far_right) + map.pos_y;
	rect_clamp(map.pos_x, map.pos_y, map.size.w, map.size.h, &p[1].x, &p[1].y);
	line(doom->surface, MM_VIEW_COLOR, p);
}

void	draw_map(t_doom *doom)
{
	int s;
	int w;
	t_i2 vec[2];
	t_map map = doom->map;
	t_xyz where = doom->player.where;
	t_sector *sect;

	s = -1;
	while (++s < doom->nb.sectors)
	{
		w = -1;
		sect = &doom->sectors[s];
		if (sect->floor.y > doom->player.where.z || sect->ceiling.y < doom->player.where.z)
			continue ;
		while (++w < sect->npoints)
		{
			//if (sect->wall[w]->n != -1)
			//	continue ; 
			vec[0].x = doom->w2 + (sect->wall[w]->v1.x - where.x) * MM_SECTORS_SCALE;
			vec[0].y = doom->h2 + (sect->wall[w]->v1.y - where.y) * MM_SECTORS_SCALE;
			vec[1].x = doom->w2 + (sect->wall[w]->v2.x - where.x) * MM_SECTORS_SCALE;
			vec[1].y = doom->h2 + (sect->wall[w]->v2.y - where.y) * MM_SECTORS_SCALE;
			if (cohen_sutherland(vec, map.size))
				line(doom->surface, sect->wall[w]->n != -1 ? 0xffff0000 : 0xFFFFFFFF, vec);	
		}
		
	}
}

void	map_area(t_doom *doom)
{
	int x;
	int y;
	Uint32*	pixels = doom->surface->pixels;
	t_map map = doom->map;


	y = map.size.y1 - MM_BEZEL_SIZE;
	while (y <= map.size.y2 + MM_BEZEL_SIZE)
	{
		x = map.size.x1 - MM_BEZEL_SIZE;
		while (x <= map.size.x2 + MM_BEZEL_SIZE)
		{
			if (x < map.size.x1 || x > map.size.x2 || y < map.size.y1 || y > map.size.y2)
				pixels[y * doom->surface->w + x] = MM_BEZEL_COLOR;
			else if (MM_ALPHA > 0)
				pixels[y * doom->surface->w + x] = blend_alpha(pixels[y * doom->surface->w + x], 0, MM_ALPHA);
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
	int h;

	map = &doom->map;
	h = doom->surface->h * (float)MM_SCALE;
	map->size = rect_xy2(doom->w2 - h / 2,
							doom->h2 - h / 2,
							doom->w2 + h / 2,
							doom->h2 + h / 2);
	map->pos_x = doom->w2;
	map->pos_y = doom->h2;
}
