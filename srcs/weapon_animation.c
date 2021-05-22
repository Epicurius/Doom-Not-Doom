/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:23:36 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/22 18:52:24 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	blit_weapon(t_doom *doom)
{
	t_rect dstr;
	t_rect srcr;
	t_bxpm *bxpm;
	t_weapon *weapon;

	if (doom->player.equiped < 0)
		return ;
	weapon = &doom->weapon[doom->player.equiped];
	bxpm = &weapon->bxpm[weapon->frame];
	dstr = rect_xy2(doom->w2,
					doom->surface->h - (float)(bxpm->h * weapon->scale),
					doom->w2 + (float)(bxpm->w * weapon->scale),
					doom->surface->h);
	srcr = rect_xy2(0,	0,	weapon->bxpm[weapon->frame].w,	weapon->bxpm[weapon->frame].h);
	blit_bxpm_scaled(doom->surface, dstr, &weapon->bxpm[weapon->frame], srcr);
}

void	weapon_animate(t_doom *doom, t_weapon *weapon)
{
	if (weapon->frame == 0 && weapon->ammo_amount > 0)
		Mix_PlayChannel(CHANNEL_WEAPON, doom->sound[weapon->sound], 0);
	if (weapon->time - doom->time.curr < -(weapon->frame_rate))
	{
		if (!weapon->frame)
		{
			doom->player.shooting = 1;
 			weapon->ammo_amount -= 1;
		}
		weapon->frame++;
		weapon->time = doom->time.curr;
	}
	if (weapon->frame >= weapon->frames)
		weapon->frame = 0;
}

void	equip_weapon(t_doom *doom)
{
	if (doom->key.num >= 1 && doom->key.num <= 3 && doom->weapon[doom->key.num - 1].own)
		doom->player.equiped = doom->key.num - 1;
}

void	precompute_weapon(t_doom *doom)
{
	t_weapon *weapon;

	equip_weapon(doom);
	if (doom->player.equiped < 0)
		return ;
	weapon = &doom->weapon[doom->player.equiped];
	doom->player.shooting = 0;
	if (weapon->frame || (doom->key.lmouse && weapon->ammo_amount > 0))
		weapon_animate(doom, weapon);
	//else if (doom->key.lmouse && weapon->ammo_amount <= 0)
		//play empty clip sound
}
