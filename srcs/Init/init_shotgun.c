/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shotgun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 15:43:43 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/24 10:14:14 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_shotgun(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 1;
	weapon->price = 100;
	weapon->damage = 100;
	weapon->ammo_price = 101;
	weapon->damage_price = 102;
	weapon->firerate_price = 103;
	weapon->max_ammo_price = 104;
	weapon->mag_size = 2;
	weapon->mag_ammo = 2;
	weapon->cur_ammo = 20;
	weapon->max_ammo = 100;
	weapon->fire_frames = 5;
	weapon->reload_frames = 9;
	weapon->frame = 0;
	weapon->frame_rate = 100;
	weapon->x_offset = 1.5;
	weapon->time = doom->time.curr;
	weapon->sound = WAV_SHOTGUN;
	weapon->scale = 0.25 * (doom->surface->w / 350);
	weapon->ammo_increase = 4;
	weapon->damage_increase = 5;
	weapon->firerate_increase = -5;
	weapon->max_ammo_increase = 4;
}
