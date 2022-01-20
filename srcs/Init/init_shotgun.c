/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/07/23 15:43:43 nneronin
 * Updated: 2022/01/20 17:13:11 Niklas Neronin
 */

#include "doom.h"

void	init_shotgun(t_doom *doom, t_weapon *weapon)
{
	weapon->own = FALSE;
	weapon->price = 100;
	weapon->damage = 50;
	weapon->ammo_price = 50;
	weapon->damage_price = 200;
	weapon->firerate_price = 200;
	weapon->max_ammo_price = 200;
	weapon->mag_size = 2;
	weapon->mag_ammo = 0;
	weapon->cur_ammo = 40;
	weapon->max_ammo = 40;
	weapon->fire_frames = 5;
	weapon->reload_frames = 9;
	weapon->frame = 0;
	weapon->frame_rate = 100;
	weapon->x_offset = 10;
	weapon->time = doom->time.curr;
	weapon->sound = WAV_SHOTGUN;
	weapon->ammo_increase = 20;
	weapon->damage_increase = 10;
	weapon->firerate_increase = -5;
	weapon->max_ammo_increase = 20;
}
