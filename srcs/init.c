/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 09:15:26 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/26 09:13:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// void	init_key(t_doom *doom)
// {
// 	doom->keys[K_A].key = SDLK_a;
// 	doom->keys[K_B].key = SDLK_b;
// 	doom->keys[K_C].key = SDLK_c;
// 	doom->keys[K_D].key = SDLK_d;
// 	doom->keys[K_E].key = SDLK_e;
// 	doom->keys[K_F].key = SDLK_f;
// 	doom->keys[K_G].key = SDLK_g;
// 	doom->keys[K_H].key = SDLK_h;
// 	doom->keys[K_I].key = SDLK_i;
// 	doom->keys[K_J].key = SDLK_j;
// 	doom->keys[K_K].key = SDLK_k;
// 	doom->keys[K_L].key = SDLK_l;
// 	doom->keys[K_M].key = SDLK_m;
// 	doom->keys[K_N].key = SDLK_n;
// 	doom->keys[K_O].key = SDLK_o;
// 	doom->keys[K_P].key = SDLK_p;
// 	doom->keys[K_Q].key = SDLK_q;
// 	doom->keys[K_R].key = SDLK_r;
// 	doom->keys[K_S].key = SDLK_s;
// 	doom->keys[K_T].key = SDLK_t;
// 	doom->keys[K_U].key = SDLK_u;
// 	doom->keys[K_V].key = SDLK_v;
// 	doom->keys[K_W].key = SDLK_w;
// 	doom->keys[K_X].key = SDLK_x;
// 	doom->keys[K_Y].key = SDLK_y;
// 	doom->keys[K_Z].key = SDLK_z;
// 	doom->keys[K_0].key = SDLK_0;
// 	doom->keys[K_1].key = SDLK_1;
// 	doom->keys[K_2].key = SDLK_2;
// 	doom->keys[K_3].key = SDLK_3;
// 	doom->keys[K_4].key = SDLK_4;
// 	doom->keys[K_5].key = SDLK_5;
// 	doom->keys[K_6].key = SDLK_6;
// 	doom->keys[K_7].key = SDLK_7;
// 	doom->keys[K_8].key = SDLK_8;
// 	doom->keys[K_9].key = SDLK_9;
// 	doom->keys[K_SPACE].key = SDLK_SPACE;
// 	doom->keys[K_LCTRL].key = SDLK_LCTRL;
// 	doom->keys[K_LSHIFT].key = SDLK_LSHIFT;
// 	doom->keys[K_TAB].key = SDLK_TAB;
// 	doom->keys[K_EQUAL].key = SDLK_EQUALS;
// 	doom->keys[K_LMOUSE].key = SDL_BUTTON_LEFT;
// }

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
	//init_key(doom);
}
