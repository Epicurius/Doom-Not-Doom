/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/10 18:04:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Draws the player view fustrum edges on the minimap.
 */
static void	map_player(t_doom *doom)
{
	t_map		map;
	t_point		p[2];
	t_player	player;

	map = doom->map;
	player = doom->player;
	p[0] = map.pos;
	p[1].x = (player.anglecos * FAR_Z - player.anglesin * doom->cam.far_left)
		+ map.pos.x;
	p[1].y = (player.anglesin * FAR_Z + player.anglecos * doom->cam.far_left)
		+ map.pos.y;
	cohen_sutherland(p, map.size);
	draw_line(doom->surface, MM_VIEW_COLOR, p[0], p[1]);
	p[0] = map.pos;
	p[1].x = (player.anglecos * FAR_Z - player.anglesin * doom->cam.far_right)
		+ map.pos.x;
	p[1].y = (player.anglesin * FAR_Z + player.anglecos * doom->cam.far_right)
		+ map.pos.y;
	cohen_sutherland(p, map.size);
	draw_line(doom->surface, MM_VIEW_COLOR, p[0], p[1]);
}

/*
 *	Draws the wall.
 */
static void	draw_minimap2(t_doom *doom, t_wall *wall)
{
	t_v3		where;
	t_point		p[2];

	where = doom->player.where;
	p[0].x = doom->c.x + (wall->v1.x - where.x) * doom->map.zoom;
	p[0].y = doom->c.y + (wall->v1.y - where.y) * doom->map.zoom;
	p[1].x = doom->c.x + (wall->v2.x - where.x) * doom->map.zoom;
	p[1].y = doom->c.y + (wall->v2.y - where.y) * doom->map.zoom;
	if (cohen_sutherland(p, doom->map.size))
	{
		if (wall->n != -1)
			draw_line(doom->surface, 0xFFFF0000, p[0], p[1]);
		else
			draw_line(doom->surface, 0xFFFFFFFF, p[0], p[1]);
	}
}

/*
 *	Loop that draws the all the walls.
 */
static void	draw_minimap(t_doom *doom)
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
		if (sect->floor.height > where.z || sect->ceiling.height < where.z)
			continue ;
		doom->sectbool[s] = TRUE;
		while (++w < sect->npoints)
		{
			if (sect->wall[w]->n != -1 && doom->sectbool[sect->wall[w]->n])
				continue ;
			draw_minimap2(doom, sect->wall[w]);
		}
	}
}

/*
 *	Draw the minimap border aswell as shading the minimap area.
 */
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

/*
 *	Main minimap draw function.
 *	If Tab is pressed draw minimap.
 */
void	map(t_doom *doom)
{
	if (doom->keys[SDL_SCANCODE_TAB])
	{
		precompute_buymenu(doom);
		reset_sectbool(doom, -1);
		doom->map.zoom = ft_clamp(doom->map.zoom, 1, 10);
		map_area(doom);
		draw_minimap(doom);
		map_player(doom);
	}
}
