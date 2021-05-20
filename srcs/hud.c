/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:12:37 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/20 13:15:56 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//		printf("%s\n", SDL_GetPixelFormatName(surf->format->format));
void	health(t_doom *doom)
{
	char		*str;
	SDL_Rect	dstr;
	TTF_Font	*amaz;
	SDL_Surface *surf;

	amaz = TTF_OpenFont(GAME_PATH"resources/TTF/AmazDoom.ttf", 50);
	str = ft_itoa(doom->player.hp);
	surf = TTF_RenderText_Blended(amaz, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr = (SDL_Rect){10, doom->surface->h - surf->h, surf->w, surf->h};
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	blit_bxpm(doom->surface, &doom->icon[0], 10 + surf->w + 10, dstr.y);
	free(str);
	SDL_FreeSurface(surf);

	str = ft_itoa(doom->player.armour);
	surf = TTF_RenderText_Blended(amaz, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr.y = dstr.y - surf->h;
	dstr.w = surf->w;
	dstr.h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	blit_bxpm(doom->surface, &doom->icon[1], 10 + surf->w + 10, dstr.y);
	free(str);
	SDL_FreeSurface(surf);

	str = ft_itoa(doom->weapon[doom->player.equiped].ammo_amount);
	surf = TTF_RenderText_Blended(amaz, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr.y = dstr.y - surf->h;
	dstr.w = surf->w;
	dstr.h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	blit_bxpm(doom->surface, &doom->icon[2], 10 + surf->w + 10, dstr.y);
	free(str);
	SDL_FreeSurface(surf);

	str = ft_itoa(doom->inv.dosh);
	surf = TTF_RenderText_Blended(amaz, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr.y = dstr.y - surf->h;
	dstr.w = surf->w;
	dstr.h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	blit_bxpm(doom->surface, &doom->icon[3], 10 + surf->w + 10, dstr.y);
	free(str);
	SDL_FreeSurface(surf);

	TTF_CloseFont(amaz);
}

void	draw_hud(t_doom *doom)
{
	health(doom);
}
