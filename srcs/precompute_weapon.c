/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:23:36 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/25 14:53:01 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	weapon_fire_animate(t_doom *doom, t_weapon *weapon)
{
	if (weapon->frame == 0 && weapon->mag_ammo > 0)
		;//Mix_PlayChannel(CHANNEL_WEAPON, doom->sound[weapon->sound], 0);
	if (weapon->time - doom->time.curr < -(weapon->frame_rate))
	{
		if (!weapon->frame)
		{
			doom->player.shooting = 1;
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
	if (weapon->time - doom->time.curr < -(weapon->frame_rate))
	{
		weapon->frame++;
		weapon->time = doom->time.curr;
	}
	if (weapon->frame >= weapon->reload_frames + weapon->fire_frames || !weapon->reload_frames)
	{
		weapon->frame = 0;
		weapon->mag_ammo = ft_min(weapon->mag_size, weapon->cur_ammo);
		weapon->cur_ammo -= ft_min(weapon->mag_size, weapon->cur_ammo);
	}
	
}
void	equip_weapon(t_doom *doom)
{
	if (doom->key.num >= 1 && doom->key.num <= 4 && doom->weapon[doom->key.num - 1].own)
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
	if (weapon->frame && weapon->frame < weapon->fire_frames || (doom->key.lmouse && weapon->mag_ammo > 0))
		weapon_fire_animate(doom, weapon);
	else if (weapon->frame >= weapon->fire_frames)
		weapon_reload_animate(doom, weapon);
	else if (doom->key.r && !weapon->frame && !weapon->mag_ammo && weapon->cur_ammo)
		weapon_reload_animate(doom, weapon);
		//weapon->frame = weapon->fire_frames;

}
