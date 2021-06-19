/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/19 17:18:47 by nneronin         ###   ########.fr       */
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

/* mtx[4] = clock */
static void	load_mtx(t_bxpm *mtx)
{
	if (!read_bxpm(&mtx[0], BXPM_PATH"bh.bxpm")
		|| !read_bxpm(&mtx[1], BXPM_PATH"vent.bxpm")
		|| !read_bxpm(&mtx[2], BXPM_PATH"tile_floor.bxpm")
		|| !read_bxpm(&mtx[3], BXPM_PATH"bars.bxpm")
		|| !read_bxpm(&mtx[5], BXPM_PATH"DoomScore.bxpm")
		|| !read_bxpm(&mtx[6], BXPM_PATH"lava.bxpm")
		|| !read_bxpm(&mtx[7], BXPM_PATH"metal_wall.bxpm")
		|| !read_bxpm(&mtx[8], BXPM_PATH"door.bxpm")
		|| !read_bxpm(&mtx[9], BXPM_PATH"console.bxpm")
		|| !read_bxpm(&mtx[10], BXPM_PATH"green_wall.bxpm")
		|| !read_bxpm(&mtx[11], BXPM_PATH"radar.bxpm")
		|| !read_bxpm(&mtx[12], BXPM_PATH"steel.bxpm")
		|| !read_bxpm(&mtx[13], BXPM_PATH"wall_panel.bxpm")
		|| !read_bxpm(&mtx[14], BXPM_PATH"metal_tile2.bxpm"))
		error_msg("Loading bxpm. (mtx)\n");
}

static void	load_stx(t_bxpm *stx)
{
	if (!read_bxpm(&stx[0], BXPM_PATH"space3.bxpm")
		|| !read_bxpm(&stx[1], BXPM_PATH"space0.bxpm")
		|| !read_bxpm(&stx[2], BXPM_PATH"space1.bxpm")
		|| !read_bxpm(&stx[3], BXPM_PATH"space2.bxpm")
		|| !read_bxpm(&stx[4], BXPM_PATH"space4.bxpm")
		|| !read_bxpm(&stx[5], BXPM_PATH"space5.bxpm"))
		error_msg("Loading bxpm. (stx1)\n");
	if (!read_bxpm(&stx[6], BXPM_PATH"land4.bxpm")
		|| !read_bxpm(&stx[7], BXPM_PATH"land1.bxpm")
		|| !read_bxpm(&stx[8], BXPM_PATH"land2.bxpm")
		|| !read_bxpm(&stx[9], BXPM_PATH"land3.bxpm")
		|| !read_bxpm(&stx[10], BXPM_PATH"land0.bxpm")
		|| !read_bxpm(&stx[11], BXPM_PATH"land5.bxpm"))
		error_msg("Loading bxpm. (stx2)\n");
}

static void	load_sheet(t_bxpm *bxpm)
{
	if (!read_bxpm(&bxpm[0], BXPM_PATH"alfred.bxpm")
		|| !read_bxpm(&bxpm[1], BXPM_PATH"spooky.bxpm")
		|| !read_bxpm(&bxpm[2], BXPM_PATH"rift.bxpm")
		|| !read_bxpm(&bxpm[3], BXPM_PATH"objects.bxpm"))
		error_msg("Loading bxpm. (etitity)\n");
}

void	init_textures(t_doom *doom)
{
	init_clock(doom, &doom->mtx[4]);
	load_mtx(doom->mtx);
	load_stx(doom->stx);
	load_sheet(doom->sprite_sheets);
	color_palets(doom);
	init_icon(doom);
}
