/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 08:39:43 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/27 13:36:18 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_ttf(t_doom *doom)
{
	if (TTF_Init())
		error_msg("Could not init TTF: %s\n", SDL_GetError());
	doom->font.amaz = TTF_OpenFont(TTF_PATH"AmazDoom.ttf", doom->settings.size.y / 20);
	if (!doom->font.amaz)
		error_msg("Could not open font: %s\n", TTF_GetError());
	doom->font.digital = TTF_OpenFont(TTF_PATH"Digital.ttf", 100);
	if (!doom->font.digital)
		error_msg("Could not open font: %s\n", TTF_GetError());
}

static void	init_sdl2(t_doom *doom)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		error_msg("Could not init SDL: %s\n", SDL_GetError());
	doom->win = SDL_CreateWindow("DOOM", 0, 0, doom->settings.size.x,
			doom->settings.size.y, 0);
	if (!doom->win)
		error_msg("Could not create window: %s\n", SDL_GetError());
	doom->surface = SDL_CreateRGBSurfaceWithFormat(0,
			doom->settings.size.x * doom->settings.rres,
			doom->settings.size.y * doom->settings.rres,
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
	if (!set_icon(doom->win, GAME_PATH"resources/ICON/DND.bmp"))
		error_msg("Could not set icon: %s\n", SDL_GetError());
}

void	init_sdl(t_doom *doom)
{
	init_sdl2(doom);
	init_ttf(doom);
}
