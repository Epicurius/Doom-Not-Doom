/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:25:14 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/18 14:18:34 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Creates a BMP of the game and save it in ./ScreenShots/.
 *	NOTE: All pause menu text will not be written to screen shot.
 */
static t_bmp	*s_to_save_screen_shot(t_doom *doom)
{
	SDL_Rect	dstr;
	TTF_Font	*amaz;
	SDL_Surface	*surface;

	amaz = TTF_OpenFont(TTF_PATH"AmazDoom.ttf", 25);
	surface = TTF_RenderText_Blended(amaz, "'S' to Save Screen Shot",
			hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){doom->surface->w - surface->w - 10,
		doom->surface->h - surface->h, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
	TTF_CloseFont(amaz);
	return (surface_to_bmp(doom->surface->w, doom->surface->h, 3,
		doom->surface->pixels));
}

/*
 *	Blits Y/N to surface.
 */
static void	y_or_n(t_doom *doom, int y)
{
	SDL_Rect	dstr;
	SDL_Surface	*surface;

	surface = TTF_RenderText_Blended(doom->font.amaz,
			"Y/N", hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){doom->c.x - surface->w / 2, y, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
}

/*
 *	Quit? loop wait for player to press y, n, esc or q.
 */
static void	quit_loop(t_doom *doom, t_bmp *bmp)
{
	int			i;
	SDL_Event	event;

	i = FALSE;
	while (1)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)
		{
			doom->quit = FALSE;
			break ;
		}
		if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_y)
			|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q))
			break ;
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
 *	Draws Quit? screen aswell as handling events.
 */
void	game_quit(t_doom *doom)
{
	t_bxpm	bxpm;
	t_bmp	*bmp;
	int		x;
	int		y;

	if (doom->quit != 1)
		return ;
	SDL_CaptureMouse(1);
	SDL_GetMouseState(&x, &y);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_WarpMouseInWindow(doom->win, doom->c.x, doom->c.y);
	bmp = s_to_save_screen_shot(doom);
	if (!read_bxpm(&bxpm, BXPM_PATH"quit.bxpm"))
		error_msg(0, "quit.bxpm");
	blit_bxpm(doom->surface, &bxpm, doom->c.x - bxpm.w / 2,
		doom->c.y - bxpm.h / 2);
	y_or_n(doom, doom->c.y + bxpm.h / 2);
	update_screen(doom);
	quit_loop(doom, bmp);
	free_bmp(bmp);
	ft_bzero(&doom->keys, 517);
	SDL_WarpMouseInWindow(doom->win, x, y);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_CaptureMouse(0);
	doom->time.curr = SDL_GetTicks();
}
