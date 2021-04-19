/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:43:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/19 16:11:35 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	mouse(t_doom *doom, SDL_Event *event)
{
	if (event->button.button == SDL_BUTTON_LEFT)
			doom->player.shooting = event->type == SDL_MOUSEBUTTONDOWN;
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
