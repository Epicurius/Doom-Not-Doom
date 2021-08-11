/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:11 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/11 12:36:33 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Frees everythign that was allocated.
 *	And quits SDL, Mix and TTF.
 */
void	free_doom(t_doom *doom)
{
	free_tpool(&doom->tpool);
	free_map(doom);
	free_entities(doom);
	free_rifts(doom);
	free_sprites_pos(doom);
	free_projectiles(doom);
	free_textures(doom);
	free_icon(doom);
	free_weapons(doom);
	SDL_FreeSurface(doom->time.surf);
	free_render_utils(doom);
	free_font(doom);
	free_sounds(doom);
	SDL_FreeSurface(doom->surface);
	SDL_DestroyTexture(doom->texture);
	SDL_DestroyRenderer(doom->renderer);
	SDL_DestroyWindow(doom->win);
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
}
