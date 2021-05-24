/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:25:14 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/24 17:00:17 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	y_or_n(t_doom *doom, int y)
{
	SDL_Rect	dstr;
	TTF_Font	*amaz;
	SDL_Surface	*surface;

	amaz = TTF_OpenFont(GAME_PATH"resources/TTF/AmazDoom.ttf", 50);
	surface = TTF_RenderText_Blended(amaz, "Y/N", hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){	doom->w2 - surface->w / 2, y, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
	TTF_CloseFont(amaz);
}

void	quit_loop(t_doom *doom)
{
	SDL_Event event;

	while (1)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)
		{
			doom->quit = 0;
			break ;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_y
				|| event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
			break ;
	}
}

void	game_quit(t_doom *doom)
{
	t_bxpm		*bxpm;

	bxpm = malloc(sizeof(t_bxpm));
	if (!bxpm)
		error_msg(0, "game_over malloc");
	if (!read_bxpm(bxpm, GAME_PATH"resources/BXPM/quit.bxpm"))
		error_msg(0, "read game_over");
	blit_bxpm(doom->surface, bxpm,
			doom->w2 - bxpm->w / 2, doom->h2 - bxpm->h / 2);
	y_or_n(doom, doom->h2 + bxpm->h / 2);
	update_screen(doom, doom->surface);
	quit_loop(doom);
	free_bxpm(bxpm);
}
