/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:23:36 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/05 14:15:51 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	blit_weapon(t_doom *doom)
{
	t_rect dstr;
	t_rect srcr;
	t_bxpm *bxpm;
	t_weapon *weapon;

	weapon = &doom->weapon[doom->player.equiped];
	bxpm = &weapon->bxpm[weapon->frame];
	dstr = new_rect(doom->w2,
					doom->surface->h - (float)(bxpm->h * weapon->scale),
					doom->w2 + (float)(bxpm->w * weapon->scale),
					doom->surface->h);
	//dstr = new_rect(doom->w2, doom->h2, doom->w2 + bxpm->w, doom->h2 + bxpm->h);
	srcr = new_rect(0,	0,	weapon->bxpm[weapon->frame].w,	weapon->bxpm[weapon->frame].h);
	blit_bxpm_scaled(doom->surface, dstr, &weapon->bxpm[weapon->frame], srcr);
}

void	weapon_animate(t_doom *doom, t_weapon *weapon)
{

	if (weapon->time - doom->time.curr < -(100))
	{
		if (!weapon->frame)
			doom->player.shooting = 1;
		weapon->frame++;
		weapon->time = doom->time.curr;
	}
	if (weapon->frame >= weapon->frames)
		weapon->frame = 0;
}

void	precompute_weapon(t_doom *doom)
{
	t_weapon *weapon;

	weapon = &doom->weapon[doom->player.equiped];
	doom->player.shooting = 0;
	if (weapon->frame || doom->key.lmouse)
		weapon_animate(doom, weapon);
}
