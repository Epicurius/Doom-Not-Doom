/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_buy_menu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 15:34:12 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/30 15:23:52 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//ft_printf("{CLR:78}Buymenu_new Done!{RESET}\n");
void	precompute_buy_menu(t_doom *doom)
{
	Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_ELEVATOR_MUSIC], -1);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	buymenu_new(doom->win, doom->renderer, doom->surface, &doom->inv);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	doom->time.curr = SDL_GetTicks();
	ft_bzero(&doom->keys, sizeof(char) * (SDL_NUM_SCANCODES + 5));
	Mix_PlayChannel(CHANNEL_MUSIC, doom->sound[WAV_MAIN_THEME], -1);
}
