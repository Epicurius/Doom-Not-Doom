/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gargoyl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:34:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/03 17:39:31 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	idle_pos(t_rect **pos)
{
	pos[0][0] = rect_xy2(229, 97, 287, 172);
}

void	init_gargoyl(t_doom *doom)
{
	t_npc_bxpm	*img;

	img = &doom->npc_bxpm[GARGOYL];
	img->bxpm = &doom->etx[3];
	img->nb[IDLE][FRAMES] = 1;
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
