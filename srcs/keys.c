/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:43:38 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/26 14:54:53 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	key_up(t_doom *doom, SDL_Event *event)
{
	if (event->key.keysym.sym == 't')
		doom->key.t = doom->key.t == 0;
	else if (event->key.keysym.sym == 'p')
		doom->key.p = doom->key.p == 0;
	else if (event->key.keysym.sym == 'l')
		doom->player.shooting = 1;

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
		key_up(doom, event);
	//else if (event->type == SDL_KEYDOWN)
	//	key_down(doom, event);
	else
		return (0);
	return (1);
}
