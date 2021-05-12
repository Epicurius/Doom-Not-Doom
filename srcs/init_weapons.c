/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:47:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/12 13:49:50 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_shotgun(t_doom *doom, t_weapon *weapon)
{
	weapon->frames = 15;
	weapon->frame = 0;
	weapon->frame_rate = 100;
	weapon->time = doom->time.curr;
	weapon->sound = SHOTGUN;
	weapon->scale = 0.7 * (doom->surface->w / 1000.0);
	weapon->bxpm = ft_memalloc(sizeof(t_bxpm) * weapon->frames);
}

static void	init_gun(t_doom *doom, t_weapon *weapon)
{
	weapon->frames = 6;
	weapon->frame = 0;
	weapon->frame_rate = 50;
	weapon->sound = GUN;
	weapon->time = doom->time.curr;
	weapon->scale = 0.7 * (doom->surface->w / 1000.0);
	weapon->bxpm = ft_memalloc(sizeof(t_bxpm) * weapon->frames);
}

static void	init_minigun(t_doom *doom, t_weapon *weapon)
{
	weapon->frames = 6;
	weapon->frame = 0;
	weapon->frame_rate = 30;
	weapon->sound = GUN;
	weapon->time = doom->time.curr;
	weapon->scale = 1.3 * (doom->surface->w / 1000.0);
	weapon->bxpm = ft_memalloc(sizeof(t_bxpm) * weapon->frames);
}

void	init_weapons(t_doom *doom)
{
	init_shotgun(doom, &doom->weapon[0]);
	init_gun(doom, &doom->weapon[1]);
	init_minigun(doom, &doom->weapon[2]);
}
