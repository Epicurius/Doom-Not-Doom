/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

static void	idle_pos_spooky(t_rect **pos)
{
	pos[0][4] = rect_xy2(25, 193, 139, 377);
	pos[0][5] = rect_xy2(172, 193, 308, 377);
	pos[0][6] = rect_xy2(325, 193, 471, 377);
	pos[0][7] = rect_xy2(494, 193, 618, 377);
	pos[0][0] = rect_xy2(654, 193, 775, 377);
	pos[0][1] = rect_xy2(821, 193, 945, 377);
	pos[0][2] = rect_xy2(968, 193, 1113, 377);
	pos[0][3] = rect_xy2(1132, 193, 1265, 377);
}

static void	move_pos_spooky(t_rect **pos)
{
	pos[0][4] = rect_xy2(25, 383, 139, 570);
	pos[0][5] = rect_xy2(172, 383, 308, 570);
	pos[0][6] = rect_xy2(325, 383, 471, 570);
	pos[0][7] = rect_xy2(494, 383, 618, 570);
	pos[0][0] = rect_xy2(654, 383, 775, 570);
	pos[0][1] = rect_xy2(821, 383, 945, 570);
	pos[0][2] = rect_xy2(968, 383, 1113, 570);
	pos[0][3] = rect_xy2(1132, 383, 1265, 570);
	pos[1][4] = rect_xy2(25, 579, 139, 764);
	pos[1][5] = rect_xy2(172, 579, 308, 764);
	pos[1][6] = rect_xy2(325, 579, 471, 764);
	pos[1][7] = rect_xy2(494, 579, 618, 764);
	pos[1][0] = rect_xy2(654, 579, 775, 764);
	pos[1][1] = rect_xy2(821, 579, 945, 764);
	pos[1][2] = rect_xy2(968, 579, 1113, 764);
	pos[1][3] = rect_xy2(1132, 579, 1265, 764);
	move_pos_spooky2(pos);
}

static void	attack_pos_spooky(t_rect **pos)
{
	pos[0][0] = rect_xy2(27, 0, 138, 192);
	pos[1][0] = rect_xy2(177, 0, 288, 192);
	pos[2][0] = rect_xy2(320, 0, 443, 192);
	pos[3][0] = rect_xy2(466, 0, 600, 192);
	pos[4][0] = rect_xy2(617, 0, 751, 192);
}

static void	death_pos_spooky(t_rect **pos)
{
	pos[0][0] = rect_xy2(6, 1541, 145, 1719);
	pos[1][0] = rect_xy2(150, 1541, 284, 1706);
	pos[2][0] = rect_xy2(305, 1541, 432, 1644);
	pos[3][0] = rect_xy2(438, 1541, 583, 1637);
	pos[4][0] = rect_xy2(582, 1541, 759, 1627);
	pos[5][0] = rect_xy2(774, 1541, 941, 1627);
}

void	init_spooky(t_doom *doom)
{
	t_frames	*img;

	img = &doom->eframes[SPOOKY];
	img->bxpm = &doom->etx[1];
	img->nb[IDLE][FRAMES] = 1;
	img->nb[IDLE][ANGLES] = 8;
	img->nb[MOVE][FRAMES] = 6;
	img->nb[MOVE][ANGLES] = 8;
	img->nb[ATTACK][FRAMES] = 5;
	img->nb[ATTACK][ANGLES] = 1;
	img->nb[DEATH][FRAMES] = 6;
	img->nb[DEATH][ANGLES] = 1;
	malloc_texture_pos(img);
	idle_pos_spooky(img->pos[IDLE]);
	move_pos_spooky(img->pos[MOVE]);
	attack_pos_spooky(img->pos[ATTACK]);
	death_pos_spooky(img->pos[DEATH]);
}
