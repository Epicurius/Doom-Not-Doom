/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

void	init_kar98(t_doom *doom, t_weapon *weapon)
{
	weapon->own = FALSE;
	weapon->price = 200;
	weapon->damage = 20;
	weapon->ammo_price = 25;
	weapon->damage_price = 50;
	weapon->firerate_price = 300;
	weapon->max_ammo_price = 50;
	weapon->mag_size = 5;
	weapon->mag_ammo = 0;
	weapon->cur_ammo = 50;
	weapon->max_ammo = 50;
	weapon->fire_frames = 7;
	weapon->reload_frames = 31;
	weapon->frame = 0;
	weapon->frame_rate = 50;
	weapon->x_offset = 70;
	weapon->sound = WAV_GUN;
	weapon->time = doom->time.curr;
	weapon->ammo_increase = 20;
	weapon->damage_increase = 10;
	weapon->firerate_increase = -4;
	weapon->max_ammo_increase = 25;
}
