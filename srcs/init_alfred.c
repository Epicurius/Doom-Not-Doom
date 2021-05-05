/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_alfred.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:42:57 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/05 10:55:51 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_alfred_nb(t_texture_sheet *sprite)
{
	sprite->nb[IDLE  ][FRAMES] = 1;
	sprite->nb[IDLE  ][ANGLES] = 8;
	sprite->nb[MOVE  ][FRAMES] = 1;
	sprite->nb[MOVE  ][ANGLES] = 8;
	sprite->nb[ATTACK][FRAMES] = 6;
	sprite->nb[ATTACK][ANGLES] = 1;
	sprite->nb[DEATH ][FRAMES] = 6;
	sprite->nb[DEATH ][ANGLES] = 1;
}

int	init_alfred(t_texture_sheet *sprite)
{
	init_alfred_nb(sprite);
	if (!malloc_texture_pos(sprite))
		return (0);
	sprite->pos[0][0][4] = new_rect(0,		0,		43,		47);
	sprite->pos[0][0][5] = new_rect(88,		0,		120,	47);
	sprite->pos[0][0][6] = new_rect(164,	0,		195,	52);
	sprite->pos[0][0][7] = new_rect(239,	0,		274,	52);
	sprite->pos[0][0][0] = new_rect(318,	0,		362,	46);
	sprite->pos[0][0][1] = new_rect(377,	0,		412,	51);
	sprite->pos[0][0][2] = new_rect(456,	0,		487,	54);
	sprite->pos[0][0][3] = new_rect(531,	0,		562,	47);

	sprite->pos[1][0][4] = new_rect(0,		55,		44,		98);
	sprite->pos[1][0][5] = new_rect(48,		55, 	107,	91);
	sprite->pos[1][0][6] = new_rect(123,	55,		188,	89);
	sprite->pos[1][0][7] = new_rect(196,	55,		251,	87);
	sprite->pos[1][0][0] = new_rect(260,	55,		303,	80);
	sprite->pos[1][0][1] = new_rect(308,	55,		362,	86);
	sprite->pos[1][0][2] = new_rect(369,	55,		436,	88);
	sprite->pos[1][0][3] = new_rect(451,	55,		511,	90);

	sprite->pos[2][0][0] = new_rect(0,		103, 	33,		153);
	sprite->pos[2][1][0] = new_rect(78,		103,	114,	155);
	sprite->pos[2][2][0] = new_rect(158,	103,	202,	150);
	sprite->pos[2][3][0] = new_rect(247,	103,	315,	161);
	sprite->pos[2][4][0] = new_rect(359,	103,	447,	174);
	sprite->pos[2][5][0] = new_rect(491,	103,	594,	192);

	sprite->pos[3][0][0] = new_rect(0,		103, 	33,		153);
	sprite->pos[3][1][0] = new_rect(78,		103,	114,	155);
	sprite->pos[3][2][0] = new_rect(158,	103,	202,	150);
	sprite->pos[3][3][0] = new_rect(247,	103,	315,	161);
	sprite->pos[3][4][0] = new_rect(359,	103,	447,	174);
	sprite->pos[3][5][0] = new_rect(491,	103,	594,	192);
	return (1);
}
