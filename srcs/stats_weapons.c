/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_weapons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:02:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/19 17:04:01 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_shotgun(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 1;
	weapon->damage = 100;
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
	weapon->scale = 0.7 * (doom->surface->w / 1000.0);
	weapon->bxpm = ft_pmalloc(sizeof(t_bxpm)
			* (weapon->fire_frames + weapon->reload_frames),
			"Shotgun bxpm");
}

void	init_pump(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 1;
	weapon->damage = 100;
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
	weapon->scale = 0.6 * (doom->surface->w / 1000.0);
	weapon->bxpm = ft_pmalloc(sizeof(t_bxpm)
			* (weapon->fire_frames + weapon->reload_frames),
			"Pump bxpm");
}

void	init_gun(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 1;
	weapon->damage = 10;
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
	weapon->scale = 0.7 * (doom->surface->w / 1000.0);
	weapon->bxpm = ft_pmalloc(sizeof(t_bxpm)
			* (weapon->fire_frames + weapon->reload_frames),
			"Gun bxpm");
}

void	init_minigun(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 1;
	weapon->damage = 10;
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
	weapon->scale = 1 * (doom->surface->w / 1000.0);
	weapon->bxpm = ft_pmalloc(sizeof(t_bxpm)
			* (weapon->fire_frames + weapon->reload_frames),
			"Minigun bxpm");
}

void	init_kar98(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 1;
	weapon->damage = 1000;
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
	weapon->scale = 1.5 * (doom->surface->w / 1000.0);
	weapon->bxpm = ft_pmalloc(sizeof(t_bxpm)
			* (weapon->fire_frames + weapon->reload_frames),
			"Kar98 bxpm");
}
