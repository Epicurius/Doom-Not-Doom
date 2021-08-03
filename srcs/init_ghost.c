/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ghost.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:53 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/03 09:38:15 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	idle_pos_ghost(t_rect **pos)
{
	pos[0][4] = rect_xy2(0, 0, 132, 150);
	pos[0][5] = rect_xy2(171, 0, 278, 150);
	pos[0][6] = rect_xy2(324, 0, 483, 150);
	pos[0][7] = rect_xy2(489, 0, 632, 150);
	pos[0][0] = rect_xy2(648, 0, 771, 150);
	pos[0][1] = rect_xy2(771, 0, 917, 150);
	pos[0][2] = rect_xy2(921, 0, 1077, 150);
	pos[0][3] = rect_xy2(1122, 0, 1235, 150);
}

static void	move_pos_ghost(t_rect **pos)
{
	pos[0][4] = rect_xy2(0, 150, 132, 314);
	pos[0][5] = rect_xy2(171, 150, 278, 314);
	pos[0][6] = rect_xy2(324, 150, 483, 314);
	pos[0][7] = rect_xy2(489, 150, 632, 314);
	pos[0][0] = rect_xy2(648, 150, 771, 314);
	pos[0][1] = rect_xy2(771, 150, 917, 314);
	pos[0][2] = rect_xy2(921, 150, 1077, 314);
	pos[0][3] = rect_xy2(1122, 150, 1235, 314);
	pos[1][4] = rect_xy2(0, 314, 132, 474);
	pos[1][5] = rect_xy2(171, 314, 278, 474);
	pos[1][6] = rect_xy2(324, 314, 483, 474);
	pos[1][7] = rect_xy2(489, 314, 632, 474);
	pos[1][0] = rect_xy2(648, 314, 771, 474);
	pos[1][1] = rect_xy2(771, 314, 917, 474);
	pos[1][2] = rect_xy2(921, 314, 1077, 474);
	pos[1][3] = rect_xy2(1122, 314, 1235, 474);
	pos[2][4] = rect_xy2(0, 474, 132, 632);
	pos[2][5] = rect_xy2(171, 474, 278, 632);
	pos[2][6] = rect_xy2(324, 474, 483, 632);
	pos[2][7] = rect_xy2(489, 474, 632, 632);
	pos[2][0] = rect_xy2(648, 474, 771, 632);
	pos[2][1] = rect_xy2(771, 474, 917, 632);
	pos[2][2] = rect_xy2(921, 474, 1077, 632);
	pos[2][3] = rect_xy2(1122, 474, 1235, 632);
	pos[3][4] = rect_xy2(0, 632, 132, 792);
	pos[3][5] = rect_xy2(171, 632, 278, 792);
	pos[3][6] = rect_xy2(324, 632, 483, 792);
	pos[3][7] = rect_xy2(489, 632, 632, 792);
	pos[3][0] = rect_xy2(648, 632, 771, 792);
	pos[3][1] = rect_xy2(771, 632, 917, 792);
	pos[3][2] = rect_xy2(921, 632, 1077, 792);
	pos[3][3] = rect_xy2(1122, 632, 1235, 792);
}

static void	attack_pos_ghost(t_rect **pos)
{
	pos[0][4] = rect_xy2(0, 788, 132, 954);
	pos[0][5] = rect_xy2(171, 788, 278, 954);
	pos[0][6] = rect_xy2(324, 788, 483, 954);
	pos[0][7] = rect_xy2(489, 788, 632, 954);
	pos[0][0] = rect_xy2(648, 788, 771, 954);
	pos[0][1] = rect_xy2(771, 788, 917, 954);
	pos[0][2] = rect_xy2(921, 788, 1077, 954);
	pos[0][3] = rect_xy2(1122, 788, 1235, 954);
	pos[1][4] = rect_xy2(0, 957, 132, 1119);
	pos[1][5] = rect_xy2(171, 957, 278, 1119);
	pos[1][6] = rect_xy2(324, 957, 483, 1119);
	pos[1][7] = rect_xy2(489, 957, 632, 1119);
	pos[1][0] = rect_xy2(648, 957, 771, 1119);
	pos[1][1] = rect_xy2(771, 957, 917, 1119);
	pos[1][2] = rect_xy2(921, 957, 1077, 1119);
	pos[1][3] = rect_xy2(1122, 957, 1235, 1119);
	pos[2][4] = rect_xy2(0, 1127, 132, 1277);
	pos[2][5] = rect_xy2(171, 1127, 278, 1277);
	pos[2][6] = rect_xy2(324, 1127, 483, 1277);
	pos[2][7] = rect_xy2(489, 1127, 632, 1277);
	pos[2][0] = rect_xy2(648, 1127, 771, 1277);
	pos[2][1] = rect_xy2(771, 1127, 917, 1277);
	pos[2][2] = rect_xy2(921, 1127, 1077, 1277);
	pos[2][3] = rect_xy2(1122, 1127, 1235, 1277);
	pos[3][4] = rect_xy2(0, 1291, 132, 1437);
	pos[3][5] = rect_xy2(171, 1291, 278, 1437);
	pos[3][6] = rect_xy2(324, 1291, 483, 1437);
	pos[3][7] = rect_xy2(489, 1291, 632, 1437);
	pos[3][0] = rect_xy2(648, 1291, 771, 1437);
	pos[3][1] = rect_xy2(771, 1291, 917, 1437);
	pos[3][2] = rect_xy2(921, 1291, 1077, 1437);
	pos[3][3] = rect_xy2(1122, 1291, 1235, 1437);
	pos[4][4] = rect_xy2(0, 1449, 132, 1599);
	pos[4][5] = rect_xy2(171, 1449, 278, 1599);
	pos[4][6] = rect_xy2(324, 1449, 483, 1599);
	pos[4][7] = rect_xy2(489, 1449, 632, 1599);
	pos[4][0] = rect_xy2(648, 1449, 771, 1599);
	pos[4][1] = rect_xy2(771, 1449, 917, 1599);
	pos[4][2] = rect_xy2(921, 1449, 1077, 1599);
	pos[4][3] = rect_xy2(1122, 1449, 1235, 1599);
}

static void	death_pos_ghost(t_rect **pos)
{
	pos[0][0] = rect_xy2(148, 1601, 273, 1765);
	pos[1][0] = rect_xy2(272, 1601, 396, 1765);
	pos[2][0] = rect_xy2(395, 1601, 509, 1765);
	pos[3][0] = rect_xy2(510, 1601, 611, 1765);
	pos[4][0] = rect_xy2(611, 1601, 688, 1765);
	pos[5][0] = rect_xy2(688, 1601, 744, 1765);
	pos[6][0] = rect_xy2(744, 1601, 761, 1765);
}

void	init_ghost(t_doom *doom)
{
	t_npc_bxpm	*img;

	img = &doom->npc_bxpm[GHOST];
	img->bxpm = &doom->etx[4];
	img->nb[IDLE][FRAMES] = 1;
	img->nb[IDLE][ANGLES] = 8;
	img->nb[MOVE][FRAMES] = 4;
	img->nb[MOVE][ANGLES] = 8;
	img->nb[ATTACK][FRAMES] = 5;
	img->nb[ATTACK][ANGLES] = 8;
	img->nb[DEATH][FRAMES] = 7;
	img->nb[DEATH][ANGLES] = 1;
	malloc_texture_pos(img);
	idle_pos_ghost(img->pos[IDLE]);
	move_pos_ghost(img->pos[MOVE]);
	attack_pos_ghost(img->pos[ATTACK]);
	death_pos_ghost(img->pos[DEATH]);
}
