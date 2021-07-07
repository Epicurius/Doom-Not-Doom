/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 09:15:26 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/07 20:37:37 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_doom(t_doom *doom, t_settings init)
{
	doom->w2 = init.display_w * init.render_resolution / 2;
	doom->h2 = init.display_h * init.render_resolution / 2;
	doom->surface_center = doom->h2 * doom->surface->w + doom->w2;
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
	init_wave_mode(doom);
	init_sound(doom);
	init_inventory(doom);
	init_slope_normal(doom);
}
