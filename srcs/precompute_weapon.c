/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_weapon.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:23:36 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/21 10:24:14 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	weapon_fire_animate(t_doom *doom, t_weapon *weapon)
{
	if (weapon->frame == 0 && weapon->mag_ammo > 0)
		Mix_PlayChannel(CHANNEL_WEAPON, doom->sound[weapon->sound], 0);
	if (doom->time.curr - weapon->time > weapon->frame_rate)
	{
		if (!weapon->frame)
		{
			doom->player.action = SHOOTING;
			weapon->mag_ammo -= 1;
		}
		weapon->frame++;
		weapon->time = doom->time.curr;
	}
	if (weapon->frame >= weapon->fire_frames)
		weapon->frame = 0;
}

void	weapon_reload_animate(t_doom *doom, t_weapon *weapon)
{
	if (!weapon->frame)
		weapon->frame = weapon->fire_frames;
	if (doom->time.curr - weapon->time > weapon->frame_rate)
	{
		weapon->frame++;
		weapon->time = doom->time.curr;
	}
	if (weapon->frame >= weapon->reload_frames + weapon->fire_frames
		|| !weapon->reload_frames)
	{
		weapon->frame = 0;
		weapon->mag_ammo = ft_min(weapon->mag_size, weapon->cur_ammo);
		weapon->cur_ammo -= ft_min(weapon->mag_size, weapon->cur_ammo);
	}
}

void	equip_weapon(t_doom *doom)
{
	if (doom->key.num >= 1 && doom->key.num <= WEAPON_AMOUNT + 1
		&& doom->weapon[doom->key.num - 1].own)
		doom->player.equiped = doom->key.num - 1;
}

void	precompute_weapon(t_doom *doom)
{
	t_weapon	*weapon;
	
	doom->player.action = NONE; //move
	equip_weapon(doom);
	if (doom->player.equiped < 0)
		return ;
	weapon = &doom->weapon[doom->player.equiped];
	if (weapon->frame && weapon->frame < weapon->fire_frames
		|| (doom->key.lmouse && weapon->mag_ammo > 0))
		weapon_fire_animate(doom, weapon);
	else if (weapon->frame >= weapon->fire_frames)
		weapon_reload_animate(doom, weapon);
	else if (doom->key.r && !weapon->frame
		&& !weapon->mag_ammo && weapon->cur_ammo)
		weapon_reload_animate(doom, weapon);
}
