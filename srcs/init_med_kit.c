/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_medkit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:34:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/06 16:44:51 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	idle_pos(t_rect **pos)
{
	pos[0][0] = rect_xy2(178, 242, 206, 260);
}

static void	death_pos(t_rect **pos)
{
	pos[0][0] = rect_xy2(178, 242, 206, 260);
}

void	init_med_kit(t_doom *doom)
{
	t_npc_bxpm	*img;

	img = &doom->npc_bxpm[MED_KIT];
	img->bxpm = &doom->etx[3];
	img->nb[IDLE][FRAMES] = 1;
	img->nb[IDLE][ANGLES] = 1;
	img->nb[MOVE][FRAMES] = 0;
	img->nb[MOVE][ANGLES] = 0;
	img->nb[ATTACK][FRAMES] = 0;
	img->nb[ATTACK][ANGLES] = 0;
	img->nb[DEATH][FRAMES] = 1;
	img->nb[DEATH][ANGLES] = 1;
	malloc_texture_pos(img);
	idle_pos(img->pos[IDLE]);
	death_pos(img->pos[DEATH]);
}
