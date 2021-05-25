/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_alfred.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:42:57 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/25 16:31:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_alfred_nb(t_npc_bxpm *sprite)
{
	sprite->nb[IDLE  ][FRAMES] = 1;
	sprite->nb[IDLE  ][ANGLES] = 8;
	sprite->nb[MOVE  ][FRAMES] = 4;
	sprite->nb[MOVE  ][ANGLES] = 8;
	sprite->nb[ATTACK][FRAMES] = 6;
	sprite->nb[ATTACK][ANGLES] = 1;
	sprite->nb[DEATH ][FRAMES] = 6;
	sprite->nb[DEATH ][ANGLES] = 1;
}

int	init_alfred(t_npc_bxpm *sprite, t_bxpm *bxpm)
{
	sprite->bxpm = bxpm;
	init_alfred_nb(sprite);
	if (!malloc_texture_pos(sprite))
		return (0);
	sprite->pos[0][0][4] = rect_xy2(0,		0,		43,		47);
	sprite->pos[0][0][5] = rect_xy2(88,		0,		120,	47);
	sprite->pos[0][0][6] = rect_xy2(164,	0,		195,	52);
	sprite->pos[0][0][7] = rect_xy2(239,	0,		274,	52);
	sprite->pos[0][0][0] = rect_xy2(318,	0,		362,	46);
	sprite->pos[0][0][1] = rect_xy2(377,	0,		412,	51);
	sprite->pos[0][0][2] = rect_xy2(456,	0,		487,	54);
	sprite->pos[0][0][3] = rect_xy2(531,	0,		562,	47);

	sprite->pos[1][0][4] = rect_xy2(0,		55,		44,		98);
	sprite->pos[1][0][5] = rect_xy2(48,		55, 	107,	91);
	sprite->pos[1][0][6] = rect_xy2(123,	55,		188,	89);
	sprite->pos[1][0][7] = rect_xy2(196,	55,		251,	87);
	sprite->pos[1][0][0] = rect_xy2(260,	55,		303,	80);
	sprite->pos[1][0][1] = rect_xy2(308,	55,		362,	86);
	sprite->pos[1][0][2] = rect_xy2(369,	55,		436,	88);
	sprite->pos[1][0][3] = rect_xy2(451,	55,		511,	90);

	sprite->pos[1][1][4] = sprite->pos[1][0][4];
	sprite->pos[1][1][5] = sprite->pos[1][0][5];
	sprite->pos[1][1][6] = sprite->pos[1][0][6];
	sprite->pos[1][1][7] = sprite->pos[1][0][7];
	sprite->pos[1][1][0] = sprite->pos[1][0][0];
	sprite->pos[1][1][1] = sprite->pos[1][0][1];
	sprite->pos[1][1][2] = sprite->pos[1][0][2];
	sprite->pos[1][1][3] = sprite->pos[1][0][3];

	sprite->pos[1][2][4] = sprite->pos[1][0][4];
	sprite->pos[1][2][5] = sprite->pos[1][0][5];
	sprite->pos[1][2][6] = sprite->pos[1][0][6];
	sprite->pos[1][2][7] = sprite->pos[1][0][7];
	sprite->pos[1][2][0] = sprite->pos[1][0][0];
	sprite->pos[1][2][1] = sprite->pos[1][0][1];
	sprite->pos[1][2][2] = sprite->pos[1][0][2];
	sprite->pos[1][2][3] = sprite->pos[1][0][3];

	sprite->pos[1][3][4] = sprite->pos[1][0][4];
	sprite->pos[1][3][5] = sprite->pos[1][0][5];
	sprite->pos[1][3][6] = sprite->pos[1][0][6];
	sprite->pos[1][3][7] = sprite->pos[1][0][7];
	sprite->pos[1][3][0] = sprite->pos[1][0][0];
	sprite->pos[1][3][1] = sprite->pos[1][0][1];
	sprite->pos[1][3][2] = sprite->pos[1][0][2];
	sprite->pos[1][3][3] = sprite->pos[1][0][3];

	sprite->pos[2][0][0] = rect_xy2(0,		103, 	33,		153);
	sprite->pos[2][1][0] = rect_xy2(78,		103,	114,	155);
	sprite->pos[2][2][0] = rect_xy2(158,	103,	202,	150);
	sprite->pos[2][3][0] = rect_xy2(247,	103,	315,	161);
	sprite->pos[2][4][0] = rect_xy2(359,	103,	447,	174);
	sprite->pos[2][5][0] = rect_xy2(491,	103,	594,	192);

	sprite->pos[3][0][0] = rect_xy2(0,		103, 	33,		153);
	sprite->pos[3][1][0] = rect_xy2(78,		103,	114,	155);
	sprite->pos[3][2][0] = rect_xy2(158,	103,	202,	150);
	sprite->pos[3][3][0] = rect_xy2(247,	103,	315,	161);
	sprite->pos[3][4][0] = rect_xy2(359,	103,	447,	174);
	sprite->pos[3][5][0] = rect_xy2(491,	103,	594,	192);
	return (1);
}
