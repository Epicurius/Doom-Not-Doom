/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 09:18:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/18 15:24:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Creates the loading screen.
 *	Loads loading.bxpm and blits it to surface.
 *	Raises Window so that the loading is visible.
 */
void	game_loading(t_doom *doom)
{
	SDL_Event	event;
	t_bxpm		bxpm;

	read_bxpm(&bxpm, BXPM_PATH"loading.bxpm");
	blit_bxpm(doom->surface, &bxpm, doom->surface->w / 2 - bxpm.w / 2,
		doom->surface->h / 2 - bxpm.h / 2);
	update_screen(doom);
	SDL_RaiseWindow(doom->win);
	SDL_PollEvent(&event);
	free(bxpm.pix);
	free(bxpm.clr);
	ft_bzero(&doom->keys, 517);
	doom->time.curr = SDL_GetTicks();
}
