/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/29 15:32:56 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static inline void	parse_textures_scaled(t_bxpm *bxpm, int amount,
	const t_id_and_path *g, float scale)
{
	int	i;

	i = -1;
	while (++i < amount)
	{
		if (!read_bxpm_scaled(&bxpm[i], g[i].path, scale))
			error_msg("read_bxpm_scaled %s.", g[i].path);
	}
}

static inline void	parse_textures(t_bxpm *bxpm, int amount,
	const t_id_and_path *g)
{
	int	i;

	i = -1;
	while (++i < amount)
	{
		if (!read_bxpm(&bxpm[i], g[i].path))
			error_msg("read_bxpm %s.", g[i].path);
	}
}

void	init_textures(t_doom *doom)
{
	parse_surface_textures(doom, -1, -1);
	parse_textures(doom->etx, ENTITY_TEXTURE_AMOUNT, g_entity_textures);
	parse_textures(doom->itx, ICON_TEXTURE_AMOUNT, g_icon_textures);
	parse_textures_scaled(doom->weapon[WEAPON_SHOTGUN].bxpm,
		SHOTGUN_TEXTURE_AMOUNT, g_shotgun_textures, doom->c.x / 800.0);
	parse_textures_scaled(doom->weapon[WEAPON_GUN].bxpm,
		GLOCK_TEXTURE_AMOUNT, g_glock_textures, doom->c.x / 900.0);
	parse_textures_scaled(doom->weapon[WEAPON_KAR].bxpm,
		KAR_TEXTURE_AMOUNT, g_kar_textures, doom->c.x / 340.0);
	parse_textures_scaled(doom->weapon[WEAPON_LAUNCHER].bxpm,
		LAUNCHER_TEXTURE_AMOUNT, g_launcher_textures, doom->c.x / 800.0);
	parse_textures_scaled(doom->weapon[WEAPON_MINIGUN].bxpm,
		MINIGUN_TEXTURE_AMOUNT, g_minigun_textures, doom->c.x / 400.0);
	init_clock(doom, &doom->mtx[MAP_TEXTURE_AMOUNT - 1]);
	sector_shading(doom, -1, -1);
}
