/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:25:14 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/18 10:35:22 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	y_or_n(t_doom *doom, int y)
{
	SDL_Rect	dstr;
	SDL_Surface	*surface;

	surface = TTF_RenderText_Blended(doom->font.amaz50,
			"Y/N", hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){doom->w2 - surface->w / 2, y, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surface);
}

static void	quit_loop(t_doom *doom)
{
	SDL_Event	event;

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
	t_bxpm	*bxpm;

	bxpm = ft_pmalloc(sizeof(t_bxpm), "Game_quit bxpm.");
	if (!read_bxpm(bxpm, GAME_PATH"resources/BXPM/quit.bxpm"))
		error_msg(0, "read game_over");
	blit_bxpm(doom->surface, bxpm,
		doom->w2 - bxpm->w / 2, doom->h2 - bxpm->h / 2);
	y_or_n(doom, doom->h2 + bxpm->h / 2);
	update_screen(doom, doom->surface);
	quit_loop(doom);
	free_bxpm(bxpm);
}
