/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

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
	t_frames	*img;

	img = &doom->eframes[BARREL];
	img->bxpm = &doom->etx[3];
	img->nb[IDLE][FRAMES] = 1;
	img->nb[IDLE][ANGLES] = 1;
	img->nb[MOVE][FRAMES] = 0;
	img->nb[MOVE][ANGLES] = 0;
	img->nb[ATTACK][FRAMES] = 0;
	img->nb[ATTACK][ANGLES] = 0;
	img->nb[DEATH][FRAMES] = 7;
	img->nb[DEATH][ANGLES] = 1;
	malloc_texture_pos(img);
	idle_pos(img->pos[IDLE]);
	death_pos(img->pos[DEATH]);
}
