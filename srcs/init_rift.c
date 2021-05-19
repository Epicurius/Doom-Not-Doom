/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rift.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 17:39:41 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/19 15:52:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_rift_nb(t_texture_sheet *sprite)
{
	sprite->nb[IDLE  ][FRAMES] = 1;
	sprite->nb[IDLE  ][ANGLES] = 1;
	sprite->nb[MOVE  ][FRAMES] = 0;
	sprite->nb[MOVE  ][ANGLES] = 0;
	sprite->nb[ATTACK][FRAMES] = 0;
	sprite->nb[ATTACK][ANGLES] = 0;
	sprite->nb[DEATH ][FRAMES] = 4;
	sprite->nb[DEATH ][ANGLES] = 1;
}

int	init_rift(t_texture_sheet *sprite)
{
	init_rift_nb(sprite);
	if (!malloc_texture_pos(sprite))
		return (0);
	sprite->pos[0][0][0] = rect_xy2(0,		0,	174, 315);
	sprite->pos[3][0][0] = rect_xy2(174,	0,	351, 315);
	sprite->pos[3][1][0] = rect_xy2(351,	0,	527, 315);
	sprite->pos[3][2][0] = rect_xy2(527,	0,	689, 315);
	sprite->pos[3][3][0] = rect_xy2(689,	0,	875, 315);
	return (1);
}
