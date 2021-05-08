/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:28:56 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/08 19:13:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	game_over(t_doom *doom)
{
	SDL_Event event;
	t_bxpm bxpm[1];
	TTF_Font *amaz;
	SDL_Surface *surf;
	SDL_Rect dstr;

	amaz = TTF_OpenFont(GAME_PATH"resources/TTF/AmazDoom.ttf", 50);
	
	surf = TTF_RenderText_Solid(amaz, "Rounds Survived: 1", hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){120, 350, surf->w, surf->h};
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surf);

	surf = TTF_RenderText_Solid(amaz, "Enemies Killed: 1", hex_to_sdl_color(0xFFFFFFFF));
	dstr = (SDL_Rect){120, 400, surf->w, surf->h};
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surf);

	surf = TTF_RenderText_Solid(amaz, "Press Enter to Continue ", hex_to_sdl_color(0xFF303030));
	dstr = (SDL_Rect){doom->surface->w - surf->w, doom->surface->h - surf->h, surf->w, surf->h};
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	SDL_FreeSurface(surf);

	read_bxpm(&bxpm[0], GAME_PATH"resources/BXPM/game_over.bxpm");
	blit_bxpm(doom->surface, &bxpm[0], 100, 100);

	SDL_UpdateWindowSurface(doom->win);
	int i = 0;
	while (1)
	{
		SDL_PollEvent(&event);
		if (event.key.keysym.sym == SDLK_RETURN)
			break ;
		if (event.key.keysym.sym == SDLK_p && i == 0)
		{
			i = 1;
			char *name = ft_sprintf("DoomScore%d%d%d.bmp", doom->time.date.tm_mon,
					doom->time.date.tm_mday, doom->time.date.tm_min);
			SDL_SaveBMP(doom->surface, name);
			free(name);
		}
	}
}
