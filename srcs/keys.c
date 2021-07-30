/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:43:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/30 15:44:03 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	get_events(t_doom *doom, char *key)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			doom->quit = 1;
		if (event.key.type == SDL_KEYDOWN || event.key.type == SDL_KEYUP)
			key[event.key.keysym.scancode] = event.key.type == SDL_KEYDOWN;
		else if (event.button.type == SDL_MOUSEBUTTONDOWN || event.button.type == SDL_MOUSEBUTTONUP)
			key[SDL_NUM_SCANCODES + event.button.button] = event.button.type == SDL_MOUSEBUTTONDOWN;
	}	
}

void	poll_event(t_doom *doom)
{
	char	*key;

	key = doom->keys;
	get_events(doom, key);
	if (key[KEY_ESCAPE] || key[KEY_Q])
		doom->quit = 1;
	if (key[KEY_M])
		mute(key[KEY_M]);
	if (key[SDL_SCANCODE_GRAVE])
		doom->player.where = doom->sectors[doom->player.sector].center;
	if (doom->player.action == NONE && key[KEY_E])
		doom->player.action = CLICKING;
}
