/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minigun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:45:01 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/27 13:23:06 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_minigun(t_doom *doom, t_weapon *weapon)
{
	weapon->own = FALSE;
	weapon->price = 300;
	weapon->damage = 10;
	weapon->ammo_price = 101;
	weapon->damage_price = 102;
	weapon->firerate_price = 103;
	weapon->max_ammo_price = 104;
	weapon->mag_size = MAX_INT;
	weapon->mag_ammo = 0;
	weapon->cur_ammo = 1000;
	weapon->max_ammo = 50;
	weapon->fire_frames = 6;
	weapon->reload_frames = 0;
	weapon->frame = 0;
	weapon->frame_rate = 30;
	weapon->sound = WAV_GUN;
	weapon->x_offset = 1.2;
	weapon->time = doom->time.curr;
	weapon->scale = 0.4 * (doom->surface->w / 350);
	weapon->ammo_increase = 20;
	weapon->damage_increase = 5;
	weapon->firerate_increase = -1;
	weapon->max_ammo_increase = 20;
}
