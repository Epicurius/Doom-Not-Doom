/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_glock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:44:42 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/27 13:23:06 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_glock(t_doom *doom, t_weapon *weapon)
{
	weapon->own = FALSE;
	weapon->price = 200;
	weapon->damage = 10;
	weapon->ammo_price = 101;
	weapon->damage_price = 102;
	weapon->firerate_price = 103;
	weapon->max_ammo_price = 104;
	weapon->mag_size = 10;
	weapon->mag_ammo = 2;
	weapon->cur_ammo = 100;
	weapon->max_ammo = 100;
	weapon->fire_frames = 6;
	weapon->reload_frames = 0;
	weapon->frame = 0;
	weapon->frame_rate = 50;
	weapon->sound = WAV_GUN;
	weapon->x_offset = 1.5;
	weapon->time = doom->time.curr;
	weapon->scale = 0.17 * (doom->surface->w / 309);
	weapon->ammo_increase = 10;
	weapon->damage_increase = 5;
	weapon->firerate_increase = -2;
	weapon->max_ammo_increase = 10;
}
