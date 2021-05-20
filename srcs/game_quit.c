/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:25:14 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/20 15:56:22 by nneronin         ###   ########.fr       */
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
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_y)
			break ;
	}
}

void	game_quit(t_doom *doom)
{
	t_bxpm		*bxpm;

	bxpm = malloc(sizeof(t_bxpm));
	read_bxpm(bxpm, GAME_PATH"resources/BXPM/quit.bxpm");
	blit_bxpm(doom->surface, bxpm,
			doom->w2 - bxpm->w / 2, doom->h2 - bxpm->h / 2);
	y_or_n(doom, doom->h2 + bxpm->h / 2);
	SDL_UpdateTexture(doom->texture, NULL,
			doom->surface->pixels, doom->surface->pitch);
	SDL_RenderCopy(doom->renderer, doom->texture, NULL, NULL);
	SDL_RenderPresent(doom->renderer);
	quit_loop(doom);
	free(bxpm->pix);
	free(bxpm->clr);
	free(bxpm);
}
