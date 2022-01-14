/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/07/23 15:45:06 nneronin
 * Updated: 2021/12/28 13:24:41 nneronin
 */

#include "doom.h"

void	init_launcher(t_doom *doom, t_weapon *weapon)
{
	weapon->own = TRUE;
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
	weapon->fire_frames = 14;
	weapon->reload_frames = 0;
	weapon->frame = 0;
	weapon->frame_rate = 100;
	weapon->x_offset = -(doom->c.x / 800 * 350 / 2);
	weapon->time = doom->time.curr;
	weapon->sound = WAV_ORB;
	weapon->ammo_increase = 10;
	weapon->damage_increase = 2;
	weapon->firerate_increase = -1;
	weapon->max_ammo_increase = 10;
}
