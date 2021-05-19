/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:28:56 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/19 16:34:11 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	print_score(t_doom *doom, int *i)
{
	char	*name;
	t_bmp	*bmp;

	name = ft_sprintf("%s/DoomScore%d%d%d.bmp", GAME_PATH, doom->time.date.tm_mon + 1,
			doom->time.date.tm_mday, doom->time.date.tm_min);
	bmp = surface_to_bmp(doom->surface->w, doom->surface->h, 3,
			doom->surface->pixels);
	write_bmp(name, bmp);
	free(bmp);
	free(name);
	*i = 1;
	Mix_PlayChannel(-1, doom->sound[SS_SAVED], 0);
	Mix_VolumeChunk(doom->sound[SS_SAVED], 128);
}

void	blit_game_over(t_doom *doom)
{
	t_bxpm		*bxpm;

	bxpm = malloc(sizeof(t_bxpm));
	read_bxpm(bxpm, GAME_PATH"resources/BXPM/game_over.bxpm");
	blit_bxpm(doom->surface, bxpm, doom->surface->w * 0.05, doom->surface->h * 0.05);
	free(bxpm->clr);
	free(bxpm->pix);
	free(bxpm);
}

void	blit_game_stats(t_doom *doom)
{
	char		*str;
	SDL_Rect	dstr;
	TTF_Font	*amaz;
	SDL_Surface	*surface;

	amaz = TTF_OpenFont(GAME_PATH"resources/TTF/AmazDoom.ttf", 50);
	str = ft_sprintf("Rounds Survived %d", doom->game.round);
	surface = TTF_RenderText_Solid(amaz, str, hex_to_sdl_color(0xFFFFFFFF));
	free(str);
	dstr = (SDL_Rect){doom->surface->w * 0.05 + 10, doom->surface->h * 0.05 + 210, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
	str = ft_sprintf("Enemies Killed: %d", doom->nb.kills);
	surface = TTF_RenderText_Solid(amaz, str, hex_to_sdl_color(0xFFFFFFFF));
	free(str);
	dstr = (SDL_Rect){doom->surface->w * 0.05 + 10, doom->surface->h * 0.05 + 260, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
	surface = TTF_RenderText_Solid(amaz, "Press Enter to Continue ",
			hex_to_sdl_color(0xFF303030));
	dstr = (SDL_Rect){doom->surface->w - surface->w,
		doom->surface->h - surface->h, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
	TTF_CloseFont(amaz);
}

void	blit_screen_shot(t_doom *doom)
{
	SDL_Rect	dstr;
	TTF_Font	*amaz;
	SDL_Surface	*surface;

	amaz = TTF_OpenFont(GAME_PATH"resources/TTF/digital.ttf", 25);
	surface = TTF_RenderText_Solid(amaz, "'P' to Save Screen Shot",
			hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){	doom->surface->w - surface->w,
						doom->surface->h - surface->h,
						surface->w,
						surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
	TTF_CloseFont(amaz);
}

void	game_over(t_doom *doom)
{
	SDL_Event	event;
	int			screen_shot;

	screen_shot = 0;
	blit_game_over(doom);
	blit_game_stats(doom);
	blit_screen_shot(doom);
	SDL_UpdateTexture(doom->texture, NULL, doom->surface->pixels, doom->surface->pitch);
	SDL_RenderCopy(doom->renderer, doom->texture, NULL, NULL);
	SDL_RenderPresent(doom->renderer);
	while (1)
	{
		SDL_PollEvent(&event);
		if (event.key.keysym.sym == SDLK_RETURN)
			break ;
		if (event.key.keysym.sym == SDLK_p && !screen_shot)
			print_score(doom, &screen_shot);
	}
}
