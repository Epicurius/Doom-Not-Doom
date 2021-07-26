/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:43:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/26 15:37:25 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	mouse(t_doom *doom, SDL_Event *event)
{
	if (event->button.button == SDL_BUTTON_LEFT)
		doom->key.lmouse = event->type == SDL_MOUSEBUTTONDOWN;
}

static void	key2(t_doom *doom, SDL_Event *event, SDL_KeyboardEvent key)
{
	if (key.keysym.sym == SDLK_p)
		doom->key.p = event->type == SDL_KEYDOWN;
	else if (key.keysym.sym == SDLK_r)
		doom->key.r = event->type == SDL_KEYDOWN;
	else if (key.keysym.sym >= SDLK_1 && key.keysym.sym <= SDLK_9)
		doom->key.num = key.keysym.sym - 48;
	else if (key.keysym.sym == SDLK_m && event->type == SDL_KEYDOWN)
	{
		doom->key.m = doom->key.m == 0;
		mute(doom->key.m);
	}
	else if (key.keysym.sym == SDLK_BACKQUOTE)
		doom->player.where = doom->sectors[doom->player.sector].center;
	else if (key.keysym.sym == SDLK_EQUALS && event->type == SDL_KEYDOWN)
		doom->key.equal = 1;
	else if (key.keysym.sym == SDLK_e)
		doom->key.e = event->type == SDL_KEYDOWN;
	if (doom->player.action == NONE && doom->key.e)
		doom->player.action = CLICKING;
}

static void	key1(t_doom *doom, SDL_Event *event, SDL_KeyboardEvent key)
{
	if (key.keysym.sym == SDLK_w || key.keysym.sym == SDLK_UP)
		doom->key.w = event->type == SDL_KEYDOWN;
	else if (key.keysym.sym == SDLK_a || key.keysym.sym == SDLK_LEFT)
		doom->key.a = event->type == SDL_KEYDOWN;
	else if (key.keysym.sym == SDLK_s || key.keysym.sym == SDLK_DOWN)
		doom->key.s = event->type == SDL_KEYDOWN;
	else if (key.keysym.sym == SDLK_d || key.keysym.sym == SDLK_RIGHT)
		doom->key.d = event->type == SDL_KEYDOWN;
	else if (key.keysym.sym == SDLK_SPACE)
		doom->key.space = event->type == SDL_KEYDOWN;
	else if (key.keysym.sym == SDLK_q
		|| key.keysym.sym == SDLK_ESCAPE)
		doom->quit = 1;
	else if (key.keysym.sym == SDLK_LCTRL)
		doom->key.lctr = event->type == SDL_KEYDOWN;
	else if (key.keysym.sym == SDLK_LSHIFT)
		doom->key.lshift = event->type == SDL_KEYDOWN;
	else if (key.keysym.sym == SDLK_TAB)
		doom->key.tab = event->type == SDL_KEYDOWN;
	else
		key2(doom, event, key);
}

static void	keys(t_doom *doom, SDL_Event *event)
{
	if (event->type == SDL_QUIT)
		doom->quit = 1;
	if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
		key1(doom, event, event->key);
	if (event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEBUTTONDOWN)
		mouse(doom, event);
}

void	poll_event(t_doom *doom, SDL_Event *event)
{
	while (SDL_PollEvent(event))
		keys(doom, event);
}
