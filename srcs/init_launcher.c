/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:45:06 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 13:07:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_launcher(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 0;
	weapon->price = 500;
	weapon->damage = 100;
	weapon->ammo_price = 101;
	weapon->damage_price = 102;
	weapon->firerate_price = 103;
	weapon->max_ammo_price = 104;
	weapon->mag_size = 8;
	weapon->mag_ammo = 8;
	weapon->cur_ammo = 20;
	weapon->max_ammo = 100;
	weapon->fire_frames = 8;
	weapon->reload_frames = 0;
	weapon->frame = 0;
	weapon->frame_rate = 100;
	weapon->x_offset = 2;
	weapon->time = doom->time.curr;
	weapon->sound = WAV_ORB;
	weapon->scale = 0.3 * (doom->surface->w / 457);
	weapon->ammo_increase = 10;
	weapon->damage_increase = 2;
	weapon->firerate_increase = -1;
	weapon->max_ammo_increase = 10;
}
