/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/11 14:44:55 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	parse_textures(int amount, t_bxpm *dest, t_id_and_path *src)
{
	int	i;

	i = -1;
	while (++i < amount)
	{
		if (ft_strequ(src[i].path, "NULL"))
			continue ;
		if (!read_bxpm(&dest[src[i].id], src[i].path))
			error_msg("Reading[%d]: %s", src[i].id, src[i].path);
	}
}

void	init_textures(t_doom *doom)
{
	init_clock(doom, &doom->mtx[4]);
	parse_textures(MAP_TEXTURE_AMOUNT, doom->mtx, g_map_textures);
	parse_textures(SKYBOX_TEXTURE_AMOUNT, doom->stx, g_skybox_textures);
	parse_textures(ENTITY_TEXTURE_AMOUNT, doom->etx, g_entity_textures);
	parse_textures(ICON_TEXTURE_AMOUNT, doom->itx, g_icon_textures);
	parse_textures(SHOTGUN_TEXTURE_AMOUNT, doom->weapon[0].bxpm, g_shotgun_textures);
	parse_textures(GLOCK_TEXTURE_AMOUNT, doom->weapon[1].bxpm, g_glock_textures);
	parse_textures(MINIGUN_TEXTURE_AMOUNT, doom->weapon[2].bxpm, g_minigun_textures);
	parse_textures(KAR_TEXTURE_AMOUNT, doom->weapon[3].bxpm, g_kar_textures);
	parse_textures(PUMP_TEXTURE_AMOUNT, doom->weapon[4].bxpm, g_pump_textures);
	color_palets(doom);
}
