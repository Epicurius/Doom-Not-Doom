/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

SDL_Texture	*ui_create_texture(SDL_Renderer *renderer, t_vec2i pos)
{
	SDL_Texture	*texture;

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET, pos.x, pos.y);
	return (texture);
}

void	ui_texture_print(SDL_Texture *texture)
{
	Uint32	format;
	int		access;
	int		w;
	int		h;

	if (!texture)
	{
		LG_WARN("Texture given doesn't exist.");
		return ;
	}
	ft_printf("[%s]\n");
	SDL_QueryTexture(texture, &format, &access, &w, &h);
	ft_printf("\tw : %d\n", w);
	ft_printf("\th : %d\n", h);
	ft_printf("\tformat : %s\n", SDL_GetPixelFormatName(format));
}

void	ui_texture_fill(
		SDL_Renderer *renderer, SDL_Texture *texture, Uint32 color)
{
	t_rgba		rgba;

	rgba = hex_to_rgba(color);
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, rgba.r, rgba.g, rgba.b, rgba.a);
	SDL_RenderFillRect(renderer, NULL);
	SDL_SetRenderTarget(renderer, NULL);
}

void	ui_texture_fill_rect(
		SDL_Renderer *renderer, SDL_Texture *texture,
		Uint32 color, t_vec4i rect)
{
	t_rgba		rgba;

	rgba = hex_to_rgba(color);
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, rgba.r, rgba.g, rgba.b, rgba.a);
	SDL_RenderFillRect(renderer, &(SDL_Rect){rect.x, rect.y, rect.w, rect.h});
	SDL_SetRenderTarget(renderer, NULL);
}

void	ui_texture_draw_border(
		SDL_Renderer *renderer, SDL_Texture *texture,
		size_t thicc, Uint32 color)
{
	t_rgba		rgba;
	SDL_Rect	rect;
	size_t		i;
	int			w;
	int			h;

	i = -1;
	rgba = hex_to_rgba(color);
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, rgba.r, rgba.g, rgba.b, rgba.a);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	while (++i < thicc)
	{
		rect.x = i;
		rect.y = i;
		rect.w = w - i - 1;
		rect.h = h - i - 1;
		SDL_RenderDrawRect(renderer, &rect);
	}
	SDL_SetRenderTarget(renderer, NULL);
}
