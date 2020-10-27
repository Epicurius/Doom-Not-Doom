/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:43:38 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/27 16:27:55 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	toggle_keys(t_doom *doom, SDL_Event *event)
{
	if (event->key.keysym.sym == 't')
		doom->key.t = doom->key.t == 0;
}

int		keys(t_doom *doom, SDL_Event *event)
{
	if (event->key.keysym.sym == 'w')
		doom->key.w = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == 'a')
		doom->key.a = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == 's')
		doom->key.s = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == 'd')
		doom->key.d = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_SPACE)
		doom->key.space = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_LCTRL)
		doom->key.l_ctrl = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_LSHIFT)
		doom->key.l_shift = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == SDLK_TAB)
		doom->key.tab = event->type == SDL_KEYDOWN;
	else if (event->key.keysym.sym == 'q')
		doom->quit = 1;
	else if (event->type == SDL_KEYUP)
		toggle_keys(doom, event);
	else
		return (0);
	return (1);
}
