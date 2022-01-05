/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_buy_menu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 15:34:12 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/05 10:41:25 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Precomputes the BuyMenu.
 *	Chenges music, releases the mouse and afterward flushes the events.
 */
void	precompute_buymenu(t_doom *doom)
{
	Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_ELEVATOR_MUSIC], -1);
	SDL_ShowCursor(SDL_ENABLE);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_WarpMouseInWindow(doom->win, doom->c.x, doom->c.y);
	buymenu(doom->win, doom->surface, &doom->inv);
	Mix_PlayChannel(-1, doom->sound[WAV_BIP], 0);
	ft_bzero(&doom->keys, 517);
	doom->player.action = NONE;
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GetRelativeMouseState(NULL, NULL);
	doom->time.curr = SDL_GetTicks();
	Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_MAIN_THEME], -1);
}
