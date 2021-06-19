/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/19 15:14:41 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_icon(t_doom *doom)
{
	if (!read_bxpm(&doom->icon[0], ICON_PATH"health_heart.bxpm")
		|| !read_bxpm(&doom->icon[1], ICON_PATH"armour_shield.bxpm")
		|| !read_bxpm(&doom->icon[2], ICON_PATH"ammo_patrons.bxpm")
		|| !read_bxpm(&doom->icon[3], ICON_PATH"mag_ammo.bxpm")
		|| !read_bxpm(&doom->icon[4], ICON_PATH"cash_dosh.bxpm"))
		error_msg("Loading icon. (weapons)\n");
}

static void	init_entity_pos(t_doom *doom)
{
	init_alfred(doom);
	init_spooky(doom);
	init_rift(doom);
	init_barrel(doom);
	init_lamp(doom);
	init_torch(doom);
	init_meat_hook(doom);
}

void	init_textures(t_doom *doom)
{
	init_clock(doom);
	load_bxpm(doom);
	init_entity_pos(doom);
	color_palets(doom);
	init_icon(doom);
}
