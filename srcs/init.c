/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 09:15:26 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/19 11:33:05 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_doom(t_doom *doom, t_settings init)
{
	//doom->root = realpath("./", NULL);
	doom->w2 = init.display_w * init.render_resolution / 2;
	doom->h2 = init.display_h * init.render_resolution / 2;
	doom->c = doom->h2 * doom->surface->w + doom->w2;
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
	init_game_entity(doom);
	init_render(doom);
	init_gamemode(doom);
	init_sound(doom);
	init_inv(doom);
	precompute_slopes(doom);
}
