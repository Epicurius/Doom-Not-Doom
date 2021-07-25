/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 09:15:26 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/25 09:23:24 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_doom(t_doom *doom)
{
	doom->surface_center.x = doom->settings.size.x * doom->settings.render_resolution / 2;
	doom->surface_center.y = doom->settings.size.y * doom->settings.render_resolution / 2;
	doom->surface_center.z= doom->surface_center.y * doom->surface->w + doom->surface_center.x;
	doom->nb.processors = ft_min(sysconf(_SC_NPROCESSORS_CONF), MAX_PROCESSORS);
	doom->nb.threads = doom->surface->w / 10;
	if (!init_tpool(&doom->tpool, doom->nb.processors))
		error_msg(NULL);
	init_fps(doom);
	init_weapons(doom);
	init_camera(doom);
	init_skybox(doom);
	init_minimap(doom);
	init_textures(doom);
	init_scale(doom);
	init_player(doom);
	init_entities(doom);
	init_render(doom);
	init_game_mode(doom);
	init_sound(doom);
	init_inventory(doom);
	init_slope_normal(doom);
}
