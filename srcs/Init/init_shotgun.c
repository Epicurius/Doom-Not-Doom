/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/07/23 15:43:43 nneronin
 * Updated: 2022/01/18 17:34:21 Niklas Neronin
 */

#include "doom.h"

void	init_shotgun(t_doom *doom, t_weapon *weapon)
{
	weapon->own = FALSE;
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
	weapon->x_offset = 10;
	weapon->time = doom->time.curr;
	weapon->sound = WAV_SHOTGUN;
	weapon->ammo_increase = 4;
	weapon->damage_increase = 5;
	weapon->firerate_increase = -5;
	weapon->max_ammo_increase = 4;
}
