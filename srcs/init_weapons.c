/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:47:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/21 10:40:41 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_shotgun(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 1;
	weapon->damage = 100;
	weapon->mag_size = 1;
	weapon->ammo_amount = 3;
	weapon->frames = 15;
	weapon->frame = 0;
	weapon->frame_rate = 100;
	weapon->time = doom->time.curr;
	weapon->sound = WAV_SHOTGUN;
	weapon->scale = 0.7 * (doom->surface->w / 1000.0);
	weapon->bxpm = ft_memalloc(sizeof(t_bxpm) * weapon->frames);
}

static void	init_gun(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 1;
	weapon->damage = 10;
	weapon->mag_size = 7;
	weapon->ammo_amount = 100;
	weapon->frames = 6;
	weapon->frame = 0;
	weapon->frame_rate = 50;
	weapon->sound = WAV_GUN;
	weapon->time = doom->time.curr;
	weapon->scale = 0.7 * (doom->surface->w / 1000.0);
	weapon->bxpm = ft_memalloc(sizeof(t_bxpm) * weapon->frames);
}

static void	init_minigun(t_doom *doom, t_weapon *weapon)
{
	weapon->own = 0;
	weapon->damage = 10;
	weapon->mag_size = -1;
	weapon->ammo_amount = 100;
	weapon->frames = 6;
	weapon->frame = 0;
	weapon->frame_rate = 30;
	weapon->sound = WAV_GUN;
	weapon->time = doom->time.curr;
	weapon->scale = 1.3 * (doom->surface->w / 1000.0);
	weapon->bxpm = ft_memalloc(sizeof(t_bxpm) * weapon->frames);
}

void	init_weapons(t_doom *doom)
{
	init_shotgun(doom, &doom->weapon[WEAPON_SHOTGUN]);
	init_gun(doom, &doom->weapon[WEAPON_GUN]);
	init_minigun(doom, &doom->weapon[WEAPON_MINIGUN]);
}
