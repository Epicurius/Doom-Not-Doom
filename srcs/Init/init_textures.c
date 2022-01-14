/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/14 11:00:21 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static inline void	parse_textures_scaled(t_doom *doom, t_bxpm *bxpm,
	const t_id_and_path *g, float extra[2])
{
	int		i;
	int		amount;
	float	scale;

	scale = doom->c.x * extra[1];
	amount = extra[0];
	i = -1;
	while (++i < amount)
	{
		ft_strcpy(&doom->root[doom->rlen], g[i].path);
		if (!read_bxpm_scaled(&bxpm[i], doom->root, scale))
			LG_ERROR("read_bxpm_scaled %s.", doom->root);
	}
}

static inline void	parse_textures(t_doom *doom, t_bxpm *bxpm,
	const t_id_and_path *g, float extra[2])
{
	int		i;
	int		amount;

	amount = extra[0];
	i = -1;
	while (++i < amount)
	{
		ft_strcpy(&doom->root[doom->rlen], g[i].path);
		if (!read_bxpm(&bxpm[i], doom->root))
			LG_ERROR("read_bxpm %s.", doom->root);
	}
}

void	init_textures(t_doom *doom)
{
	parse_surface_textures(doom, -1, -1);
	parse_textures(doom, doom->etx, g_entity_textures,
		(float [2]){ENTITY_TEXTURE_AMOUNT, 0});
	parse_textures_scaled(doom, doom->itx, g_icon_textures,
		(float [2]){ICON_TEXTURE_AMOUNT, 0.002});
	parse_textures_scaled(doom, doom->weapon[WEAPON_SHOTGUN].bxpm,
		g_shotgun_textures, (float [2]){SHOTGUN_TEXTURE_AMOUNT, 0.00125});
	parse_textures_scaled(doom, doom->weapon[WEAPON_GUN].bxpm,
		g_glock_textures, (float [2]){GLOCK_TEXTURE_AMOUNT, 0.001});
	parse_textures_scaled(doom, doom->weapon[WEAPON_KAR].bxpm,
		g_kar_textures, (float [2]){KAR_TEXTURE_AMOUNT, 0.003});
	parse_textures_scaled(doom, doom->weapon[WEAPON_LAUNCHER].bxpm,
		g_launcher_textures, (float [2]){LAUNCHER_TEXTURE_AMOUNT, 0.00125});
	parse_textures_scaled(doom, doom->weapon[WEAPON_MINIGUN].bxpm,
		g_minigun_textures, (float [2]){MINIGUN_TEXTURE_AMOUNT, 0.0025});
	init_clock(doom, &doom->mtx[MAP_TEXTURE_AMOUNT - 1]);
	sector_shading(doom, -1, -1);
}
