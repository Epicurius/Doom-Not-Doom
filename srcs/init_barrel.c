/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_barrel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:09:52 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/26 15:07:29 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	idle_pos(t_rect **pos)
{
	pos[0][0] = rect_xy2(174, 182, 209, 233);
}

static void	death_pos(t_rect **pos)
{
	pos[0][0] = rect_xy2(216, 178, 257, 233);
	pos[1][0] = rect_xy2(262, 178, 307, 233);
	pos[2][0] = rect_xy2(315, 178, 362, 233);
	pos[3][0] = rect_xy2(369, 109, 456, 208);
	pos[4][0] = rect_xy2(464, 109, 544, 208);
	pos[5][0] = rect_xy2(551, 109, 630, 208);
	pos[6][0] = rect_xy2(637, 109, 713, 208);
}

void	init_barrel(t_doom *doom)
{
	t_npc_bxpm *img;

	img = &doom->npc_bxpm[BARREL];
	img->bxpm = &doom->sprite_sheets[3];
	img->nb[IDLE  ][FRAMES] = 1;
	img->nb[IDLE  ][ANGLES] = 1;
	img->nb[MOVE  ][FRAMES] = 0;
	img->nb[MOVE  ][ANGLES] = 0;
	img->nb[ATTACK][FRAMES] = 0;
	img->nb[ATTACK][ANGLES] = 0;
	img->nb[DEATH ][FRAMES] = 7;
	img->nb[DEATH ][ANGLES] = 1;
	malloc_texture_pos(img);
	idle_pos(img->pos[IDLE]);
	death_pos(img->pos[DEATH]);
}
