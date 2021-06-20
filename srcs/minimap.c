/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/20 11:03:12 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	map_player(t_doom *doom)
{
	t_map		map;
	t_point		p[2];
	t_player	player;

	map = doom->map;
	player = doom->player;
	p[0].x = map.pos_x;
	p[0].y = map.pos_y;
	p[1].x = (player.anglecos * FAR_Z - player.anglesin * doom->cam.far_left)
		+ map.pos_x;
	p[1].y = (player.anglesin * FAR_Z + player.anglecos * doom->cam.far_left)
		+ map.pos_y;
	cohen_sutherland(p, map.size);
	line(doom->surface, MM_VIEW_COLOR, p);
	p[0].x = map.pos_x;
	p[0].y = map.pos_y;
	p[1].x = (player.anglecos * FAR_Z - player.anglesin * doom->cam.far_right)
		+ map.pos_x;
	p[1].y = (player.anglesin * FAR_Z + player.anglecos * doom->cam.far_right)
		+ map.pos_y;
	cohen_sutherland(p, map.size);
	line(doom->surface, MM_VIEW_COLOR, p);
}

static void	draw_map2(t_doom *doom, t_wall *wall)
{
	t_v3		where;
	t_point		p[2];

	where = doom->player.where;
	p[0].x = doom->w2 + (wall->v1.x - where.x) * MM_SECTORS_SCALE;
	p[0].y = doom->h2 + (wall->v1.y - where.y) * MM_SECTORS_SCALE;
	p[1].x = doom->w2 + (wall->v2.x - where.x) * MM_SECTORS_SCALE;
	p[1].y = doom->h2 + (wall->v2.y - where.y) * MM_SECTORS_SCALE;
	if (cohen_sutherland(p, doom->map.size))
	{
		if (wall->n != -1)
			line(doom->surface, 0xFFFF0000, p);
		else
			line(doom->surface, 0xFFFFFFFF, p);
	}
}

static void	draw_map(t_doom *doom)
{
	int			s;
	int			w;
	t_v3		where;
	t_sector	*sect;

	s = -1;
	where = doom->player.where;
	while (++s < doom->nb.sectors)
	{
		w = -1;
		sect = &doom->sectors[s];
		if (sect->floor.y > where.z || sect->ceiling.y < where.z)
			continue ;
		while (++w < sect->npoints)
			draw_map2(doom, sect->wall[w]);
	}
}

static void	map_area(t_doom *doom)
{
	int		x;
	int		y;
	int		coord;
	t_map	map;
	Uint32	*pixels;

	map = doom->map;
	pixels = doom->surface->pixels;
	y = map.size.y1 - MM_BEZEL_SIZE;
	while (y <= map.size.y2 + MM_BEZEL_SIZE)
	{
		x = map.size.x1 - MM_BEZEL_SIZE;
		while (x <= map.size.x2 + MM_BEZEL_SIZE)
		{
			coord = y * doom->surface->w + x;
			if (x < map.size.x1 || x > map.size.x2
				|| y < map.size.y1 || y > map.size.y2)
				pixels[coord] = MM_BEZEL_COLOR;
			else if (MM_ALPHA > 0)
				pixels[coord] = blend_alpha(pixels[coord], 0, MM_ALPHA);
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
