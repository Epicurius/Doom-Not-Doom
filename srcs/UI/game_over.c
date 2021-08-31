/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:28:56 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/31 13:03:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Creates a BMP of the game over screen and save it in ./ScreenShots/.
 */
static void	print_score(t_doom *doom, int *i)
{
	char	*name;
	t_bmp	*bmp;

	name = ft_sprintf("%s/ScreenShots/DoomScore%d%d%d.bmp", GAME_PATH,
			doom->time.date.tm_mon + 1, doom->time.date.tm_mday,
			doom->time.date.tm_min);
	bmp = surface_to_bmp(doom->surface->w, doom->surface->h, 3,
			doom->surface->pixels);
	write_bmp(name, bmp);
	free_bmp(bmp);
	free(name);
	*i = TRUE;
	Mix_PlayChannel(CHANNEL_TTS, doom->sound[WAV_SCREEN_SHOT], 0);
	Mix_VolumeChunk(doom->sound[WAV_SCREEN_SHOT], 128);
}

/*
 *	Blits game_over.bxmp to screen.
 */
static void	blit_game_over(t_doom *doom)
{
	t_bxpm	*bxpm;

	bxpm = PROT_ALLOC(sizeof(t_bxpm));
	read_bxpm(bxpm, BXPM_PATH"game_over.bxpm");
	blit_bxpm(doom->surface, bxpm,
		doom->surface->w * 0.05, doom->surface->h * 0.05);
	free_bxpm(bxpm);
}

/*
 *	Draws the game stats: Rounds Survived and Enemies Killed.
 *	TODO: Find a better colour for "Press Enter..."
 */
static void	blit_endless_stats(t_doom *doom, char *str)
{
	SDL_Rect	dstr;
	SDL_Surface	*surface;

	if (doom->game.mode == ENDLESS)
	{
		str = ft_sprintf("Rounds Survived %d", doom->game.round);
		surface = TTF_RenderText_Blended(doom->font.amaz, str,
				hex_to_sdl_color(0xFFFFFFFF));
		free(str);
		dstr = (SDL_Rect){doom->surface->w * 0.05 + 10,
			doom->surface->h * 0.05 + 210, surface->w, surface->h};
		SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
		SDL_FreeSurface(surface);
		str = ft_sprintf("Enemies Killed: %d", doom->nb.kills);
		surface = TTF_RenderText_Blended(doom->font.amaz, str,
				hex_to_sdl_color(0xFFFFFFFF));
		free(str);
		dstr = (SDL_Rect){doom->surface->w * 0.05 + 10,
			doom->surface->h * 0.05 + 260, surface->w, surface->h};
		SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
		SDL_FreeSurface(surface);
	}
}

/*
 *	Blit "'P' to Save Screen Shot" to surface.
 */
static void	blit_info(t_doom *doom)
{
	SDL_Rect	dstr;
	TTF_Font	*amaz;
	SDL_Surface	*surface;

	surface = TTF_RenderText_Blended(doom->font.amaz,
			"Press Enter to Continue ", hex_to_sdl_color(0xFF303030));
	dstr = (SDL_Rect){doom->surface->w - surface->w,
		doom->surface->h - surface->h, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
	amaz = TTF_OpenFont(TTF_PATH"digital.ttf", 25);
	surface = TTF_RenderText_Blended(amaz, "'P' to Save Screen Shot",
			hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){doom->surface->w - surface->w,
		doom->surface->h - surface->h, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
	TTF_CloseFont(amaz);
}

/*
 *	Draws game over screen and handels events for exiting and screen shots.
 */
void	game_over(t_doom *doom)
{
	SDL_Event	event;
	int			screen_shot;

	screen_shot = FALSE;
	blit_game_over(doom);
	blit_endless_stats(doom, NULL);
	blit_info(doom);
	update_screen(doom);
	Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_PLAYER_DEATH], 0);
	while (1)
	{
		SDL_PollEvent(&event);
		if (event.key.keysym.sym == SDLK_RETURN)
			break ;
		if (event.key.keysym.sym == SDLK_p && !screen_shot)
			print_score(doom, &screen_shot);
	}
}
