/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_pause.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:11:48 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/20 16:24:33 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	s_to_save_screen_shot(t_doom *doom)
{
	SDL_Rect	dstr;
	TTF_Font	*amaz;
	SDL_Surface	*surface;

	amaz = TTF_OpenFont(GAME_PATH"resources/TTF/AmazDoom.ttf", 25);
	surface = TTF_RenderText_Blended(amaz, "'S' to Save Screen Shot",
			hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){	doom->surface->w - surface->w,
						doom->surface->h - surface->h,
						surface->w,
						surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
	TTF_CloseFont(amaz);
}

static void	pause_loop(t_doom *doom, t_bxpm *bxpm, t_bmp *bmp)
{
	int	i;
	SDL_Event event;

	i = 0;
	while (1)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
		{
			doom->key.p = 0;
			break ;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
		{
			doom->quit = 1;
			break ;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s && !i)
		{
			write_bmp("Pause.bmp", bmp);
			Mix_PlayChannel(-1, doom->sound[WAV_SCREEN_SHOT], 0);
			Mix_VolumeChunk(doom->sound[WAV_SCREEN_SHOT], 128);
			i = 1;
		}
	}
}

static void	p_to_unpause(t_doom *doom, int y)
{
	SDL_Rect	dstr;
	TTF_Font	*amaz;
	SDL_Surface	*surface;

	amaz = TTF_OpenFont(GAME_PATH"resources/TTF/AmazDoom.ttf", 50);
	surface = TTF_RenderText_Blended(amaz, "'P' to unpause", hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){	doom->w2 - surface->w / 2, y, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
	TTF_CloseFont(amaz);
}

void	game_pause(t_doom *doom)
{
	t_bxpm		*bxpm;
	t_bmp		*bmp;

	bmp = surface_to_bmp(doom->surface->w, doom->surface->h, 3,
			doom->surface->pixels);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	bxpm = malloc(sizeof(t_bxpm));
	read_bxpm(bxpm, GAME_PATH"resources/BXPM/pause.bxpm");
	blit_bxpm(doom->surface, bxpm,
			doom->w2 - bxpm->w / 2, doom->h2 - bxpm->h / 2);
	s_to_save_screen_shot(doom);
	p_to_unpause(doom, doom->h2 + bxpm->h / 2);
	update_screen(doom, doom->surface);;
	pause_loop(doom, bxpm, bmp);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	free_bmp(bmp);
	free_bxpm(bxpm);
}