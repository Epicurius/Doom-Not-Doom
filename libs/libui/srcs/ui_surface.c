/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

SDL_Surface	*ui_surface_new(int w, int h)
{
	return (SDL_CreateRGBSurface(0, w, h, 32,
			0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000));
}

void	ui_surface_fill(SDL_Surface *surface, Uint32 color)
{
	SDL_FillRect(surface, NULL, color);
}

void	ui_surface_fill_rect(SDL_Surface *surface, Uint32 color, t_vec4i rect)
{
	t_rgba	rgba;

	rgba = hex_to_rgba(color);
	SDL_FillRect(surface, &(SDL_Rect){rect.x, rect.y, rect.w, rect.h}, color);
}

void	ui_surface_pixel_set(SDL_Surface *surface, int x, int y, Uint32 color)
{
	Uint32	*pixels;

	if (!(x >= 0 && x < surface->w && y >= 0 && y < surface->h))
		return ;
	pixels = surface->pixels;
	pixels[y * surface->w + x] = color;
}

Uint32	ui_surface_pixel_get(SDL_Surface *surface, int x, int y)
{
	Uint32	*pixels;

	if (!(x >= 0 && x < surface->w && y >= 0 && y < surface->h))
		return (1);
	pixels = surface->pixels;
	return (pixels[y * surface->w + x]);
}
