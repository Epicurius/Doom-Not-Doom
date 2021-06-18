/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:12:37 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/18 10:38:12 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	hud_health(t_doom *doom)
{
	char		*str;
	SDL_Rect	dstr;
	SDL_Surface	*surf;

	str = ft_itoa(doom->player.hp);
	surf = TTF_RenderText_Blended(doom->font.amaz50, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr = (SDL_Rect){10, doom->surface->h - surf->h, surf->w, surf->h};
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	blit_bxpm(doom->surface, &doom->icon[0], 10 + surf->w + 10, dstr.y);
	free(str);
	SDL_FreeSurface(surf);
}

void	hud_armour(t_doom *doom)
{
	char		*str;
	SDL_Rect	dstr;
	SDL_Surface	*surf;

	str = ft_itoa(doom->player.armour);
	surf = TTF_RenderText_Blended(doom->font.amaz50, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr.y = dstr.y - surf->h;
	dstr.w = surf->w;
	dstr.h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	blit_bxpm(doom->surface, &doom->icon[1], 10 + surf->w + 10, dstr.y);
	free(str);
	SDL_FreeSurface(surf);
}

void	hud_currammo(t_doom *doom)
{
	char		*str;
	SDL_Rect	dstr;
	SDL_Surface	*surf;

	str = ft_itoa(doom->weapon[doom->player.equiped].cur_ammo);
	surf = TTF_RenderText_Blended(doom->font.amaz50, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr.y = dstr.y - surf->h;
	dstr.w = surf->w;
	dstr.h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	blit_bxpm(doom->surface, &doom->icon[2], 10 + surf->w + 10, dstr.y);
	free(str);
	SDL_FreeSurface(surf);
}

void	hud_magammo(t_doom *doom)
{
	char		*str;
	SDL_Rect	dstr;
	SDL_Surface	*surf;

	str = ft_itoa(doom->weapon[doom->player.equiped].mag_ammo);
	surf = TTF_RenderText_Blended(doom->font.amaz50, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr.y = dstr.y - surf->h;
	dstr.w = surf->w;
	dstr.h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	blit_bxpm(doom->surface, &doom->icon[3], 10 + surf->w + 10, dstr.y);
	free(str);
	SDL_FreeSurface(surf);
}

void	hud_dosh(t_doom *doom)
{
	char		*str;
	SDL_Rect	dstr;
	SDL_Surface	*surf;

	str = ft_itoa(doom->inv.dosh);
	surf = TTF_RenderText_Blended(doom->font.amaz50, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr.y = dstr.y - surf->h;
	dstr.w = surf->w;
	dstr.h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, &dstr);
	blit_bxpm(doom->surface, &doom->icon[4], 10 + surf->w + 10, dstr.y);
	free(str);
	SDL_FreeSurface(surf);
}
