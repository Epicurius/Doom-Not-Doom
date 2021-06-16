/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 09:18:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/16 09:25:42 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	game_loading(t_doom *doom)
{
	SDL_Event	event;
	t_bxpm		*bxpm;

	bxpm = malloc(sizeof(t_bxpm));
	if (!bxpm)
		error_msg("Game loading malloc.\n");
	read_bxpm(bxpm, GAME_PATH"resources/BXPM/game_loading.bxpm");
	blit_bxpm(doom->surface, bxpm, doom->surface->w / 2 - bxpm->w / 2,
		doom->surface->h / 2 - bxpm->h / 2);
	update_screen(doom, doom->surface);
	SDL_PollEvent(&event);
	SDL_RaiseWindow(doom->win);
	free_bxpm(bxpm);
}
