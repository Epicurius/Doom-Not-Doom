/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_meat_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:42:57 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 12:25:06 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	idle_pos(t_rect **pos)
{
	pos[0][0] = rect_xy2(543, 5, 579, 104);
}

void	init_meat_hook(t_doom *doom)
{
	t_npc_bxpm	*img;

	img = &doom->npc_bxpm[MEAT_HOOK];
	img->bxpm = &doom->sprite_sheets[3];
	img->nb[IDLE][FRAMES] = 1;
	img->nb[IDLE][ANGLES] = 1;
	img->nb[MOVE][FRAMES] = 0;
	img->nb[MOVE][ANGLES] = 0;
	img->nb[ATTACK][FRAMES] = 0;
	img->nb[ATTACK][ANGLES] = 0;
	img->nb[DEATH][FRAMES] = 0;
	img->nb[DEATH][ANGLES] = 0;
	malloc_texture_pos(img);
	idle_pos(img->pos[IDLE]);
}
