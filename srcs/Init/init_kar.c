/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/07/23 15:44:54 nneronin
 * Updated: 2022/01/20 17:12:57 Niklas Neronin
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
