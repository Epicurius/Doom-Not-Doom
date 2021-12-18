/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:25:14 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/18 13:45:01 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
static void	quit_loop(t_doom *doom)
{
	SDL_Event	event;

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
	}
}

/*
 *	Draws Quit? screen aswell as handling events.
 */
void	game_quit(t_doom *doom)
{
	t_bxpm	*bxpm;
	int		x;
	int		y;

	if (doom->quit != 1)
		return ;
	SDL_CaptureMouse(1);
	SDL_GetMouseState(&x, &y);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	bxpm = protalloc(sizeof(t_bxpm));
	if (!read_bxpm(bxpm, BXPM_PATH"quit.bxpm"))
		error_msg(0, "read game_over");
	blit_bxpm(doom->surface, bxpm,
		doom->c.x - bxpm->w / 2, doom->c.y - bxpm->h / 2);
	y_or_n(doom, doom->c.y + bxpm->h / 2);
	update_screen(doom);
	quit_loop(doom);
	free_bxpm(bxpm);
	ft_bzero(&doom->keys, 517);
	SDL_WarpMouseInWindow(doom->win, x, y);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_CaptureMouse(0);
	doom->time.curr = SDL_GetTicks();
}
