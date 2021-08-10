/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:12:37 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/25 12:04:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	hud_health(t_doom *doom, SDL_Rect *dstr)
{
	char		*str;
	SDL_Surface	*surf;

	str = ft_itoa(doom->player.health);
	surf = TTF_RenderText_Blended(doom->font.amaz50, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr->y = dstr->y - surf->h;
	dstr->w = surf->w;
	dstr->h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, dstr);
	blit_bxpm(doom->surface, &doom->itx[0], 10 + surf->w + 10, dstr->y);
	free(str);
	SDL_FreeSurface(surf);
}

void	hud_armour(t_doom *doom, SDL_Rect *dstr)
{
	char		*str;
	SDL_Surface	*surf;

	str = ft_itoa(doom->player.armour);
	surf = TTF_RenderText_Blended(doom->font.amaz50, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr->y = dstr->y - surf->h;
	dstr->w = surf->w;
	dstr->h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, dstr);
	blit_bxpm(doom->surface, &doom->itx[1], 10 + surf->w + 10, dstr->y);
	free(str);
	SDL_FreeSurface(surf);
}

void	hud_curr_ammo(t_doom *doom, SDL_Rect *dstr)
{
	char		*str;
	SDL_Surface	*surf;

	str = ft_itoa(doom->weapon[doom->player.equiped].cur_ammo);
	surf = TTF_RenderText_Blended(doom->font.amaz50, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr->y = dstr->y - surf->h;
	dstr->w = surf->w;
	dstr->h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, dstr);
	blit_bxpm(doom->surface, &doom->itx[2], 10 + surf->w + 10, dstr->y);
	free(str);
	SDL_FreeSurface(surf);
}

void	hud_mag_ammo(t_doom *doom, SDL_Rect *dstr)
{
	char		*str;
	SDL_Surface	*surf;

	str = ft_itoa(doom->weapon[doom->player.equiped].mag_ammo);
	surf = TTF_RenderText_Blended(doom->font.amaz50, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr->y = dstr->y - surf->h;
	dstr->w = surf->w;
	dstr->h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, dstr);
	blit_bxpm(doom->surface, &doom->itx[3], 10 + surf->w + 10, dstr->y);
	free(str);
	SDL_FreeSurface(surf);
}

void	hud_dosh(t_doom *doom, SDL_Rect *dstr)
{
	char		*str;
	SDL_Surface	*surf;

	str = ft_itoa(doom->inv.dosh);
	surf = TTF_RenderText_Blended(doom->font.amaz50, str, doom->time.color);
	if (!surf)
		error_msg("TTF_RenderText_Blended error: %s\n", TTF_GetError());
	dstr->y = dstr->y - surf->h;
	dstr->w = surf->w;
	dstr->h = surf->h;
	SDL_BlitSurface(surf, NULL, doom->surface, dstr);
	blit_bxpm(doom->surface, &doom->itx[4], 10 + surf->w + 10, dstr->y);
	free(str);
	SDL_FreeSurface(surf);
}