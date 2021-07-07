/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_weapons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:02:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/07 11:09:39 by jsalmi           ###   ########.fr       */
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
	weapon->bxpm = ft_pmalloc(sizeof(t_bxpm)
			* (weapon->fire_frames + weapon->reload_frames), "Shotgun bxpm");
	bxpm_shotgun(weapon);
	weapon->scale = 0.25 * (doom->surface->w / weapon->bxpm[0].w);
}

void	init_glock(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 1;
	weapon->price = 200;
	weapon->damage = 10;
	weapon->ammo_price = 101;
	weapon->damage_price = 102;
	weapon->firerate_price = 103;
	weapon->max_ammo_price = 104;
	weapon->mag_size = 10;
	weapon->mag_ammo = 2;
	weapon->cur_ammo = 100;
	weapon->max_ammo = 100;
	weapon->fire_frames = 6;
	weapon->reload_frames = 0;
	weapon->frame = 0;
	weapon->frame_rate = 50;
	weapon->sound = WAV_GUN;
	weapon->x_offset = 1.5;
	weapon->time = doom->time.curr;
	weapon->bxpm = ft_pmalloc(sizeof(t_bxpm)
			* (weapon->fire_frames + weapon->reload_frames), "Glock bxpm");
	bxpm_glock(weapon);
	weapon->scale = 0.17 * (doom->surface->w / weapon->bxpm[0].w);
}

void	init_minigun(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 1;
	weapon->price = 300;
	weapon->damage = 10;
	weapon->ammo_price = 101;
	weapon->damage_price = 102;
	weapon->firerate_price = 103;
	weapon->max_ammo_price = 104;
	weapon->mag_size = MAX_INT;
	weapon->mag_ammo = 0;
	weapon->cur_ammo = 1000;
	weapon->max_ammo = 50;
	weapon->fire_frames = 6;
	weapon->reload_frames = 0;
	weapon->frame = 0;
	weapon->frame_rate = 30;
	weapon->sound = WAV_GUN;
	weapon->x_offset = 1.2;
	weapon->time = doom->time.curr;
	weapon->bxpm = ft_pmalloc(sizeof(t_bxpm)
			* (weapon->fire_frames + weapon->reload_frames), "Minigun bxpm");
	bxpm_minigun(weapon);
	weapon->scale = 0.4 * (doom->surface->w / weapon->bxpm[0].w);
}

void	init_kar98(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 1;
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
	weapon->x_offset = 1.3;
	weapon->sound = WAV_GUN;
	weapon->time = doom->time.curr;
	weapon->bxpm = ft_pmalloc(sizeof(t_bxpm)
			* (weapon->fire_frames + weapon->reload_frames), "Kar98 bxpm");
	bxpm_kar98(weapon);
	weapon->scale = 0.35 * (doom->surface->w / weapon->bxpm[0].w);
}

void	init_pump(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 1;
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
	weapon->fire_frames = 9;
	weapon->reload_frames = 0;
	weapon->frame = 0;
	weapon->frame_rate = 100;
	weapon->x_offset = 1.5;
	weapon->time = doom->time.curr;
	weapon->sound = WAV_SHOTGUN;
	weapon->bxpm = ft_pmalloc(sizeof(t_bxpm)
			* (weapon->fire_frames + weapon->reload_frames), "Pump bxpm");
	bxpm_pump(weapon);
	weapon->scale = 0.3 * (doom->surface->w / weapon->bxpm[0].w);
}
