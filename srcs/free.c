/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:11 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/20 12:44:30 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free_doom(t_doom *doom)
{
	ft_printf("{CLR:142}In FREE!\n{RESET}");
	free_map(doom);
	free_sprites(doom);
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
	free_tpool(&doom->tpool);
	SDL_FreeSurface(doom->surface);
	SDL_DestroyTexture(doom->texture);
	SDL_DestroyRenderer(doom->renderer);
	SDL_DestroyWindow(doom->win);
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
	free(doom);
	ft_printf("{GREEN}Done FREE!\n{RESET}");
}
