/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 09:15:26 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/30 14:24:50 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	get_surface_center(t_doom *doom)
{
	doom->c.x = (doom->settings.size.x * doom->settings.rresolution) / 2;
	doom->c.y = (doom->settings.size.y * doom->settings.rresolution) / 2;
	doom->c.z = doom->c.y * doom->surface->w + doom->c.x;
}

void	init_doom(t_doom *doom)
{
	doom->nb.processors = ft_min(sysconf(_SC_NPROCESSORS_CONF), MAX_PROCESSORS);
	doom->nb.threads = doom->surface->w / 10;
	if (!init_tpool(&doom->tpool, doom->nb.processors))
		error_msg(NULL);
	get_surface_center(doom);
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
