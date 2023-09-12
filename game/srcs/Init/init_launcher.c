/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

void	init_launcher(t_doom *doom, t_weapon *weapon)
{
	weapon->own = FALSE;
	weapon->price = 300;
	weapon->damage = 100;
	weapon->ammo_price = 100;
	weapon->damage_price = 500;
	weapon->firerate_price = 200;
	weapon->max_ammo_price = 250;
	weapon->mag_size = 10;
	weapon->mag_ammo = 0;
	weapon->cur_ammo = 10;
	weapon->max_ammo = 10;
	weapon->fire_frames = 14;
	weapon->reload_frames = 0;
	weapon->frame = 0;
	weapon->frame_rate = 100;
	weapon->x_offset = -(doom->c.x / 800 * 350 / 2);
	weapon->time = doom->time.curr;
	weapon->sound = WAV_ORB;
	weapon->ammo_increase = 5;
	weapon->damage_increase = 100;
	weapon->firerate_increase = -1;
	weapon->max_ammo_increase = 5;
}
