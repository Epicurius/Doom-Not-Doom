/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 08:39:43 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/20 13:54:56 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_ttf(t_doom *doom)
{
	if (TTF_Init())
		error_msg("Could not init TTF: %s\n", SDL_GetError());
	doom->font.amaz50 = TTF_OpenFont(TTF_PATH"AmazDoom.ttf", 50);
	if (!doom->font.amaz50)
		error_msg("Could not open font: %s\n", TTF_GetError());
	doom->font.digi50 = TTF_OpenFont(TTF_PATH"Digital.ttf", 50);
	if (!doom->font.digi50)
		error_msg("Could not open font: %s\n", TTF_GetError());
	doom->font.digi100 = TTF_OpenFont(TTF_PATH"Digital.ttf",
			100);
	if (!doom->font.digi100)
		error_msg("Could not open font: %s\n", TTF_GetError());
}

static void	init_mix(t_doom *doom)
{
	if (Mix_Init(MIX_INIT_FLAC) & MIX_INIT_FLAC != MIX_INIT_FLAC)
		error_msg("Could not init MIX: %s\n", SDL_GetError());
}

static void	init_sdl2(t_doom *doom)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		error_msg("Could not init SDL: %s\n", SDL_GetError());
	doom->win = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, doom->settings.size.x,
			doom->settings.size.y, SDL_WINDOW_SHOWN);
	if (!doom->win)
		error_msg("Could not create window: %s\n", SDL_GetError());
	doom->surface = SDL_CreateRGBSurfaceWithFormat(0,
			doom->settings.size.x * doom->settings.render_resolution,
			doom->settings.size.y * doom->settings.render_resolution,
			32, SDL_PIXELFORMAT_ARGB8888);
	if (!doom->surface)
		error_msg("Could not create surface: %s\n", SDL_GetError());
	doom->renderer = SDL_CreateRenderer(doom->win, -1,
			SDL_RENDERER_TARGETTEXTURE);
	if (!doom->renderer)
		error_msg("Could not create renderer: %s\n", SDL_GetError());
	doom->texture = SDL_CreateTexture(doom->renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, doom->surface->w, doom->surface->h);
	if (!doom->texture)
		error_msg("Could not create texture: %s\n", SDL_GetError());
	SDL_SetRelativeMouseMode(SDL_TRUE);
	if (!set_icon(doom->win, GAME_PATH"resources/ICON/DND.bmp"))
		error_msg("Could not set icon: %s\n", SDL_GetError());
}

void	init_sdl(t_doom *doom)
{
	init_sdl2(doom);
	init_ttf(doom);
	init_mix(doom);
}
