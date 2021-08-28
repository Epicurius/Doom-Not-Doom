/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rift.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 17:39:41 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/28 12:11:23 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	idle_pos(t_rect **pos)
{
	pos[0][0] = rect_xy2(0, 0, 174, 315);
}

static void	death_pos(t_rect **pos)
{
	pos[0][0] = rect_xy2(174, 0, 351, 315);
	pos[1][0] = rect_xy2(351, 0, 527, 315);
	pos[2][0] = rect_xy2(527, 0, 689, 315);
	pos[3][0] = rect_xy2(689, 0, 875, 315);
}

void	init_rift(t_doom *doom)
{
	t_frames	*img;

	img = &doom->eframes[RIFT];
	img->bxpm = &doom->etx[2];
	img->nb[IDLE][FRAMES] = 1;
	img->nb[IDLE][ANGLES] = 1;
	img->nb[MOVE][FRAMES] = 0;
	img->nb[MOVE][ANGLES] = 0;
	img->nb[ATTACK][FRAMES] = 0;
	img->nb[ATTACK][ANGLES] = 0;
	img->nb[DEATH][FRAMES] = 4;
	img->nb[DEATH][ANGLES] = 1;
	malloc_texture_pos(img);
	idle_pos(img->pos[IDLE]);
	death_pos(img->pos[DEATH]);
}
