/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_pause.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:11:48 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/10 17:18:52 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Creates a BMP of the game and save it in ./ScreenShots/.
 *	NOTE: All pause menu text will not be written to screen shot.
 */
static void	s_to_save_screen_shot(t_doom *doom)
{
	SDL_Rect	dstr;
	TTF_Font	*amaz;
	SDL_Surface	*surface;

	amaz = TTF_OpenFont(TTF_PATH"AmazDoom.ttf", 25);
	surface = TTF_RenderText_Blended(amaz, "'S' to Save Screen Shot",
			hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){doom->surface->w - surface->w,
		doom->surface->h - surface->h, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
	TTF_CloseFont(amaz);
}

/*
 *	Pause loop waits for player to unpauses, screen shot or exit.
 */
static void	pause_loop(t_doom *doom, t_bmp *bmp)
{
	int			i;
	SDL_Event	event;

	i = 0;
	while (1)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
		{
			doom->keys[SDL_SCANCODE_P] = FALSE;
			break ;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
		{
			doom->quit = TRUE;
			break ;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s && !i)
		{
			write_bmp("Pause.bmp", bmp);
			Mix_PlayChannel(CHANNEL_TTS, doom->sound[WAV_SCREEN_SHOT], 0);
			Mix_VolumeChunk(doom->sound[WAV_SCREEN_SHOT], 128);
			i = TRUE;
		}
	}
}

/*
 *	Blits "'P' to unpauses" to surface.
 */
static void	p_to_unpause(t_doom *doom, int y)
{
	SDL_Rect	dstr;
	SDL_Surface	*surface;

	surface = TTF_RenderText_Blended(doom->font.amaz,
			"'P' to unpause", hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){doom->c.x - surface->w / 2, y, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
}

/*
 *	Draws Pause screen aswell as handling events.
 */
void	game_pause(t_doom *doom)
{
	t_bxpm		*bxpm;
	t_bmp		*bmp;

	if (!doom->keys[SDL_SCANCODE_P])
		return ;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	bmp = surface_to_bmp(doom->surface->w, doom->surface->h, 3,
			doom->surface->pixels);
	bxpm = protalloc(sizeof(t_bxpm));
	read_bxpm(bxpm, BXPM_PATH"pause.bxpm");
	blit_bxpm(doom->surface, bxpm,
		doom->c.x - bxpm->w / 2, doom->c.y - bxpm->h / 2);
	s_to_save_screen_shot(doom);
	p_to_unpause(doom, doom->c.y + bxpm->h / 2);
	update_screen(doom);
	pause_loop(doom, bmp);
	free_bmp(bmp);
	free_bxpm(bxpm);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	ft_bzero(&doom->keys, 517);
	doom->time.curr = SDL_GetTicks();
}
