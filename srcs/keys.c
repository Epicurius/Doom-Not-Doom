/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:43:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/20 12:49:45 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	mouse(t_doom *doom, SDL_Event *event)
{
	if (event->button.button == SDL_BUTTON_LEFT)
			doom->key.lmouse = event->type == SDL_MOUSEBUTTONDOWN;
}

void	key(t_doom *doom, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_w)
		doom->key.w = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_a)
		doom->key.a = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_s)
		doom->key.s = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_d)
		doom->key.d = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_SPACE)
		doom->key.space = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_LCTRL)
		doom->key.l_ctrl = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_LSHIFT)
		doom->key.l_shift = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_TAB)
		doom->key.tab = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_q)
		doom->quit = 1;
	else if (event->key.keysym.sym == SDLK_p)
		doom->key.p = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym >= SDLK_1 &&
			event->key.keysym.sym <= SDLK_9)
		doom->key.num = event->key.keysym.sym - 48;
}

void	keys(t_doom *doom, SDL_Event *event)
{
	if (event->type == SDL_QUIT)
		doom->quit = 1;
	if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
		key(doom, event);
	if (event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEBUTTONDOWN)
		mouse(doom, event);
}

void	pause_game(t_doom *doom)
{
	SDL_Event *event;
	t_bxpm	bxpm[1];

	read_bxpm(&bxpm[0], GAME_PATH"resources/BXPM/pause.bxpm");
	tpool_wait(&doom->tpool);
	blit_bxpm(doom->surface, &bxpm[0], 100, 100);
	free(bxpm->clr);
	free(bxpm->pix);
	SDL_UpdateWindowSurface(doom->win);
	while (1)
	{
		SDL_PollEvent(event);
		if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_p)
		{
			doom->key.p = 0;
			break ;
		}

	}
}

void	poll_event(t_doom *doom, SDL_Event *event)
{
	while (SDL_PollEvent(event))
	{
		keys(doom, event);
		//if (doom->key.p)
		//	pause_game(doom);
	}
}
