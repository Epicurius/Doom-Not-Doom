/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

static void	idle_pos(t_rect **pos)
{
	pos[0][0] = rect_xy2(174, 7, 197, 91);
	pos[1][0] = rect_xy2(204, 7, 227, 91);
	pos[2][0] = rect_xy2(234, 7, 257, 91);
	pos[3][0] = rect_xy2(264, 7, 287, 91);
}

void	init_lamp(t_doom *doom)
{
	t_frames	*img;

	img = &doom->eframes[LAMP];
	img->bxpm = &doom->etx[3];
	img->nb[IDLE][FRAMES] = 4;
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
