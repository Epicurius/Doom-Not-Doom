/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:42:57 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/28 12:09:36 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	idle_pos(t_rect **pos)
{
	pos[0][0] = rect_xy2(371, 209, 381, 256);
	pos[1][0] = rect_xy2(383, 209, 393, 256);
	pos[2][0] = rect_xy2(395, 209, 405, 256);
	pos[3][0] = rect_xy2(407, 209, 417, 256);
	pos[4][0] = rect_xy2(419, 209, 429, 256);
}

void	init_torch(t_doom *doom)
{
	t_frames	*img;

	img = &doom->npc_bxpm[TORCH];
	img->bxpm = &doom->etx[3];
	img->nb[IDLE][FRAMES] = 5;
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
