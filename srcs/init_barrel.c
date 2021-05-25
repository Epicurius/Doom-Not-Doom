/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_barrel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:09:52 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/25 17:25:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_nb(t_npc_bxpm *sprite)
{
	sprite->nb[IDLE  ][FRAMES] = 1;
	sprite->nb[IDLE  ][ANGLES] = 1;
	sprite->nb[MOVE  ][FRAMES] = 0;
	sprite->nb[MOVE  ][ANGLES] = 0;
	sprite->nb[ATTACK][FRAMES] = 0;
	sprite->nb[ATTACK][ANGLES] = 0;
	sprite->nb[DEATH ][FRAMES] = 7;
	sprite->nb[DEATH ][ANGLES] = 1;
}

int	init_barrel(t_npc_bxpm *sprite, t_bxpm *bxpm)
{
	sprite->bxpm = bxpm;
	init_nb(sprite);
	if (!malloc_texture_pos(sprite))
		return (0);
	sprite->pos[0][0][0] = rect_xy2(4,	199, 43, 257);
	sprite->pos[3][0][0] = rect_xy2(47,	199, 90, 257);
	sprite->pos[3][1][0] = rect_xy2(93, 199, 141, 257);
	sprite->pos[3][2][0] = rect_xy2(145, 199, 197, 257);
	sprite->pos[3][3][0] = rect_xy2(199, 155, 289, 257);
	sprite->pos[3][4][0] = rect_xy2(291, 167, 377, 257);
	sprite->pos[3][5][0] = rect_xy2(379, 167, 463, 257);
	sprite->pos[3][6][0] = rect_xy2(465, 164, 545, 257);
	return (1);
}
