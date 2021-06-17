/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_alfred.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:42:57 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 12:18:27 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	idle_pos(t_rect **pos)
{
	pos[0][4] = rect_xy2(0, 0, 43, 47);
	pos[0][5] = rect_xy2(88, 0, 120, 47);
	pos[0][6] = rect_xy2(164, 0, 195, 52);
	pos[0][7] = rect_xy2(239, 0, 274, 52);
	pos[0][0] = rect_xy2(318, 0, 362, 46);
	pos[0][1] = rect_xy2(377, 0, 412, 51);
	pos[0][2] = rect_xy2(456, 0, 487, 54);
	pos[0][3] = rect_xy2(531, 0, 562, 47);
}

static void	move_pos(t_rect **pos)
{
	pos[0][4] = rect_xy2(0, 55, 44, 98);
	pos[0][5] = rect_xy2(48, 55, 107, 91);
	pos[0][6] = rect_xy2(123, 55, 188, 89);
	pos[0][7] = rect_xy2(196, 55, 251, 87);
	pos[0][0] = rect_xy2(260, 55, 303, 80);
	pos[0][1] = rect_xy2(308, 55, 362, 86);
	pos[0][2] = rect_xy2(369, 55, 436, 88);
	pos[0][3] = rect_xy2(451, 55, 511, 90);
	pos[1][4] = pos[0][4];
	pos[1][5] = pos[0][5];
	pos[1][6] = pos[0][6];
	pos[1][7] = pos[0][7];
	pos[1][0] = pos[0][0];
	pos[1][1] = pos[0][1];
	pos[1][2] = pos[0][2];
	pos[1][3] = pos[0][3];
	pos[2][4] = pos[0][4];
	pos[2][5] = pos[0][5];
	pos[2][6] = pos[0][6];
	pos[2][7] = pos[0][7];
	pos[2][0] = pos[0][0];
	pos[2][1] = pos[0][1];
	pos[2][2] = pos[0][2];
	pos[2][3] = pos[0][3];
	pos[3][4] = pos[0][4];
	pos[3][5] = pos[0][5];
	pos[3][6] = pos[0][6];
	pos[3][7] = pos[0][7];
	pos[3][0] = pos[0][0];
	pos[3][1] = pos[0][1];
	pos[3][2] = pos[0][2];
	pos[3][3] = pos[0][3];
}

static void	attack_pos(t_rect **pos)
{
	pos[0][0] = rect_xy2(0, 103, 33, 153);
	pos[1][0] = rect_xy2(78, 103, 114, 155);
	pos[2][0] = rect_xy2(158, 103, 202, 150);
	pos[3][0] = rect_xy2(247, 103, 315, 161);
	pos[4][0] = rect_xy2(359, 103, 447, 174);
	pos[5][0] = rect_xy2(491, 103, 594, 192);
}

static void	death_pos(t_rect **pos)
{
	pos[0][0] = rect_xy2(0, 103, 33, 153);
	pos[1][0] = rect_xy2(78, 103, 114, 155);
	pos[2][0] = rect_xy2(158, 103, 202, 150);
	pos[3][0] = rect_xy2(247, 103, 315, 161);
	pos[4][0] = rect_xy2(359, 103, 447, 174);
	pos[5][0] = rect_xy2(491, 103, 594, 192);
}

void	init_alfred(t_doom *doom)
{
	t_npc_bxpm	*img;

	img = &doom->npc_bxpm[ALFRED];
	img->bxpm = &doom->sprite_sheets[0];
	img->nb[IDLE][FRAMES] = 1;
	img->nb[IDLE][ANGLES] = 8;
	img->nb[MOVE][FRAMES] = 4;
	img->nb[MOVE][ANGLES] = 8;
	img->nb[ATTACK][FRAMES] = 6;
	img->nb[ATTACK][ANGLES] = 1;
	img->nb[DEATH][FRAMES] = 6;
	img->nb[DEATH][ANGLES] = 1;
	malloc_texture_pos(img);
	idle_pos(img->pos[IDLE]);
	move_pos(img->pos[MOVE]);
	attack_pos(img->pos[ATTACK]);
	death_pos(img->pos[DEATH]);
}
