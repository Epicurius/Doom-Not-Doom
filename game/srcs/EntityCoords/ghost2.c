/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

void	move_pos_ghost2(t_rect **pos)
{
	pos[2][4] = rect_xy2(10, 474, 132, 632);
	pos[2][5] = rect_xy2(171, 474, 278, 632);
	pos[2][6] = rect_xy2(324, 474, 483, 632);
	pos[2][7] = rect_xy2(489, 474, 632, 632);
	pos[2][0] = rect_xy2(648, 474, 771, 632);
	pos[2][1] = rect_xy2(771, 474, 917, 632);
	pos[2][2] = rect_xy2(921, 474, 1077, 632);
	pos[2][3] = rect_xy2(1122, 474, 1235, 632);
	pos[3][4] = rect_xy2(10, 632, 132, 792);
	pos[3][5] = rect_xy2(171, 632, 278, 792);
	pos[3][6] = rect_xy2(324, 632, 483, 792);
	pos[3][7] = rect_xy2(489, 632, 632, 792);
	pos[3][0] = rect_xy2(648, 632, 771, 792);
	pos[3][1] = rect_xy2(771, 632, 917, 792);
	pos[3][2] = rect_xy2(921, 632, 1077, 792);
	pos[3][3] = rect_xy2(1122, 632, 1235, 792);
}

void	attack_pos_ghost2(t_rect **pos)
{
	pos[2][4] = rect_xy2(10, 1127, 132, 1277);
	pos[2][5] = rect_xy2(171, 1127, 278, 1277);
	pos[2][6] = rect_xy2(324, 1127, 483, 1277);
	pos[2][7] = rect_xy2(489, 1127, 632, 1277);
	pos[2][0] = rect_xy2(648, 1127, 771, 1277);
	pos[2][1] = rect_xy2(771, 1127, 917, 1277);
	pos[2][2] = rect_xy2(921, 1127, 1077, 1277);
	pos[2][3] = rect_xy2(1122, 1127, 1235, 1277);
	pos[3][4] = rect_xy2(10, 1291, 132, 1437);
	pos[3][5] = rect_xy2(171, 1291, 278, 1437);
	pos[3][6] = rect_xy2(324, 1291, 483, 1437);
	pos[3][7] = rect_xy2(489, 1291, 632, 1437);
	pos[3][0] = rect_xy2(648, 1291, 771, 1437);
	pos[3][1] = rect_xy2(771, 1291, 917, 1437);
	pos[3][2] = rect_xy2(921, 1291, 1077, 1437);
	pos[3][3] = rect_xy2(1122, 1291, 1235, 1437);
	pos[4][4] = rect_xy2(10, 1449, 132, 1599);
	pos[4][5] = rect_xy2(171, 1449, 278, 1599);
	pos[4][6] = rect_xy2(324, 1449, 483, 1599);
	pos[4][7] = rect_xy2(489, 1449, 632, 1599);
	pos[4][0] = rect_xy2(648, 1449, 771, 1599);
	pos[4][1] = rect_xy2(771, 1449, 917, 1599);
	pos[4][2] = rect_xy2(921, 1449, 1077, 1599);
	pos[4][3] = rect_xy2(1122, 1449, 1235, 1599);
}
