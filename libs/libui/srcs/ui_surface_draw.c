/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_surface_draw_border(
		SDL_Surface *surface, size_t thiccness, Uint32 color)
{
	size_t	i;

	i = -1;
	while (++i < thiccness)
		ui_surface_rect_draw(surface, vec2i(i, i),
			vec2i(surface->w - i - 1, surface->h - i - 1), color);
}

/*
 * t_vec2i		p1;			the top left corner of the rect;
 * t_vec2i		p2;			the bot right corner of the rect;
*/
void	ui_surface_rect_draw(
		SDL_Surface *surface, t_vec2i p1, t_vec2i p2, Uint32 color)
{
	ui_surface_line_draw(surface, p1, vec2i(p2.x, p1.y), color);
	ui_surface_line_draw(surface, p1, vec2i(p1.x, p2.y), color);
	ui_surface_line_draw(surface, p2, vec2i(p1.x, p2.y), color);
	ui_surface_line_draw(surface, p2, vec2i(p2.x, p1.y), color);
}

/*
 * tl	top, left
 * br	bot, right
*/

void	ui_surface_rect_draw_thicc(
		SDL_Surface *surface, t_vec2i p1, t_vec2i p2, int thicc, Uint32 color)
{
	int		i;
	int		iter;
	t_vec2i	tl;
	t_vec2i	br;

	tl.x = ft_min(p1.x, p2.x);
	tl.y = ft_min(p1.y, p2.y);
	br.x = ft_max(p1.x, p2.x);
	br.y = ft_max(p1.y, p2.y);
	iter = ft_min(thicc, dist(tl, br));
	i = -1;
	while (++i < iter)
	{
		ui_surface_line_draw(surface,
			vec2i(tl.x, tl.y + i), vec2i(br.x, tl.y + i), color);
		ui_surface_line_draw(surface,
			vec2i(tl.x, br.y - i), vec2i(br.x, br.y - i), color);
		ui_surface_line_draw(surface,
			vec2i(tl.x + i, tl.y), vec2i(tl.x + i, br.y), color);
		ui_surface_line_draw(surface,
			vec2i(br.x - i, tl.y), vec2i(br.x - i, br.y), color);
	}
}

void	ui_surface_rect_draw_filled(
		SDL_Surface *surface, t_vec2i p1, t_vec2i p2, Uint32 color)
{
	SDL_FillRect(surface,
		&(SDL_Rect){p1.x, p1.y, p2.x - p1.x, p2.y - p1.y}, color);
}
