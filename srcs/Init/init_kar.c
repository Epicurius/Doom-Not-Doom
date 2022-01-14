/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/07/23 15:44:54 nneronin
 * Updated: 2021/12/28 13:22:21 nneronin
 */

#include "doom.h"

void	init_kar98(t_doom *doom, t_weapon *weapon)
{
	weapon->own = TRUE;
	weapon->price = 400;
	weapon->damage = 1000;
	weapon->ammo_price = 101;
	weapon->damage_price = 102;
	weapon->firerate_price = 103;
	weapon->max_ammo_price = 104;
	weapon->mag_size = 7;
	weapon->mag_ammo = 0;
	weapon->cur_ammo = 100;
	weapon->max_ammo = 200;
	weapon->fire_frames = 7;
	weapon->reload_frames = 31;
	weapon->frame = 0;
	weapon->frame_rate = 50;
	weapon->x_offset = 70;
	weapon->sound = WAV_GUN;
	weapon->time = doom->time.curr;
	weapon->ammo_increase = 10;
	weapon->damage_increase = 2;
	weapon->firerate_increase = -4;
	weapon->max_ammo_increase = 10;
}
