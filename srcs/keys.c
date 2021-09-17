/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:43:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/17 18:09:52 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Check all the keyboard events that have happened and save the to doom->keys
 *	Check all mouse button events and save them.
 */
static void	get_events(t_doom *doom, char *key)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			doom->quit = TRUE;
		else if (event.key.type == SDL_KEYDOWN
			|| event.key.type == SDL_KEYUP)
			key[event.key.keysym.scancode] = event.key.type == SDL_KEYDOWN;
		else if (event.button.type == SDL_MOUSEBUTTONDOWN
			|| event.button.type == SDL_MOUSEBUTTONUP)
			key[511 + event.button.button]
				= event.button.type == SDL_MOUSEBUTTONDOWN;
		else if (event.type == SDL_MOUSEWHEEL)
			doom->map.zoom += event.wheel.y;
	}	
}

/*
 *	After checking all the events with get_events.
 *	Check if mute or unmute.
 *	Check if tp player to center of sector. (Useful if stuck)
 *	Set player action to clicking.
 */
void	poll_event(t_doom *doom)
{
	char	*key;

	key = doom->keys;
	get_events(doom, key);
	if (key[SDL_SCANCODE_ESCAPE] || key[SDL_SCANCODE_Q])
		doom->quit = TRUE;
	if (key[SDL_SCANCODE_M])
		mute(key[SDL_SCANCODE_M] = 0);
	if (key[SDL_SCANCODE_GRAVE])
		doom->player.where = doom->sectors[doom->player.sector].center;
	if (doom->player.action == NONE && key[SDL_SCANCODE_E])
		doom->player.action = CLICKING;
	if (doom->settings.debug && key[SDL_SCANCODE_F])
		doom->player.flight = doom->player.flight == FALSE;
}
