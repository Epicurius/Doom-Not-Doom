/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

void	init_minigun(t_doom *doom, t_weapon *weapon)
{
	weapon->own = FALSE;
	weapon->price = 300;
	weapon->damage = 10;
	weapon->ammo_price = 300;
	weapon->damage_price = 200;
	weapon->firerate_price = 400;
	weapon->max_ammo_price = 50;
	weapon->mag_size = MAX_INT;
	weapon->mag_ammo = 0;
	weapon->cur_ammo = 50;
	weapon->max_ammo = 50;
	weapon->fire_frames = 6;
	weapon->reload_frames = 0;
	weapon->frame = 0;
	weapon->frame_rate = 30;
	weapon->sound = WAV_GUN;
	weapon->x_offset = 0;
	weapon->time = doom->time.curr;
	weapon->ammo_increase = 50;
	weapon->damage_increase = 10;
	weapon->firerate_increase = -1;
	weapon->max_ammo_increase = 50;
}
