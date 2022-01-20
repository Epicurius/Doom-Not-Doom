/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/07/23 15:44:42 nneronin
 * Updated: 2022/01/20 17:01:28 Niklas Neronin
 */

#include "doom.h"

void	init_glock(t_doom *doom, t_weapon *weapon)
{
	weapon->own = TRUE;
	weapon->price = 0;
	weapon->damage = 10;
	weapon->ammo_price = 10;
	weapon->damage_price = 100;
	weapon->firerate_price = 100;
	weapon->max_ammo_price = 50;
	weapon->mag_size = 8;
	weapon->mag_ammo = 8;
	weapon->cur_ammo = 100;
	weapon->max_ammo = 100;
	weapon->fire_frames = 6;
	weapon->reload_frames = 0;
	weapon->frame = 0;
	weapon->frame_rate = 50;
	weapon->sound = WAV_GUN;
	weapon->x_offset = 120;
	weapon->time = doom->time.curr;
	weapon->ammo_increase = 100;
	weapon->damage_increase = 10;
	weapon->firerate_increase = -2;
	weapon->max_ammo_increase = 100;
}
