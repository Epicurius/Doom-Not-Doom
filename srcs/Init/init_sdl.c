/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 08:39:43 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/07 17:04:36 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_ttf(t_doom *doom)
{
	if (TTF_Init())
		LG_ERROR("Could not init TTF: %s\n", SDL_GetError());
	doom->font.amaz = TTF_OpenFont(TTF_PATH"AmazDoom.ttf",
			doom->settings.size.y / 20);
	if (!doom->font.amaz)
		LG_ERROR("Could not open font: %s\n", TTF_GetError());
	doom->font.digital = TTF_OpenFont(TTF_PATH"Digital.ttf", 100);
	if (!doom->font.digital)
		LG_ERROR("Could not open font: %s\n", TTF_GetError());
}

static void	init_sdl2(t_doom *doom, int x, int y)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		LG_ERROR("Could not init SDL: %s\n", SDL_GetError());
	doom->win = SDL_CreateWindow("DOOM", x, y,
			doom->settings.size.x, doom->settings.size.y, 0);
	if (!doom->win)
		LG_ERROR("Could not create window: %s\n", SDL_GetError());
	doom->surface = SDL_CreateRGBSurfaceWithFormat(0,
			doom->settings.size.x * doom->settings.rres,
			doom->settings.size.y * doom->settings.rres,
			32, SDL_PIXELFORMAT_ARGB8888);
	if (!doom->surface)
		LG_ERROR("Could not create surface: %s\n", SDL_GetError());
	doom->renderer = SDL_CreateRenderer(doom->win, -1,
			SDL_RENDERER_TARGETTEXTURE);
	if (!doom->renderer)
		LG_ERROR("Could not create renderer: %s\n", SDL_GetError());
	doom->texture = SDL_CreateTexture(doom->renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, doom->surface->w, doom->surface->h);
	if (!doom->texture)
		LG_ERROR("Could not create texture: %s\n", SDL_GetError());
	if (!set_icon(doom->win, GAME_PATH"resources/ICON/DND.bmp"))
		LG_ERROR("Could not set icon: %s\n", SDL_GetError());
}

void	init_sdl(t_doom *doom)
{
	if (DND_WIN)
		init_sdl2(doom, 0, 30);
	else
		init_sdl2(doom, 0, 0);
	init_ttf(doom);
}
