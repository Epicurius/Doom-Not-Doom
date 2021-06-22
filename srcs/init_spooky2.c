/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_spooky2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:53 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/20 11:23:15 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	move_pos_spooky2(t_rect **pos)
{
	pos[3][4] = rect_xy2(25, 965, 139, 1152);
	pos[3][5] = rect_xy2(172, 965, 308, 1152);
	pos[3][6] = rect_xy2(325, 965, 471, 1152);
	pos[3][7] = rect_xy2(494, 965, 618, 1152);
	pos[3][0] = rect_xy2(654, 965, 775, 1152);
	pos[3][1] = rect_xy2(821, 965, 945, 1152);
	pos[3][2] = rect_xy2(968, 965, 1113, 1152);
	pos[3][3] = rect_xy2(1132, 965, 1265, 1152);
	pos[4][4] = rect_xy2(25, 1158, 139, 1344);
	pos[4][5] = rect_xy2(172, 1158, 308, 1344);
	pos[4][6] = rect_xy2(325, 1158, 471, 1344);
	pos[4][7] = rect_xy2(494, 1158, 618, 1344);
	pos[4][0] = rect_xy2(654, 1158, 775, 1344);
	pos[4][1] = rect_xy2(821, 1158, 945, 1344);
	pos[4][2] = rect_xy2(968, 1158, 1113, 1344);
	pos[4][3] = rect_xy2(1132, 1158, 1265, 1344);
	pos[5][4] = rect_xy2(25, 1350, 139, 1536);
	pos[5][5] = rect_xy2(172, 1350, 308, 1536);
	pos[5][6] = rect_xy2(325, 1350, 471, 1536);
	pos[5][7] = rect_xy2(494, 1350, 618, 1536);
	pos[5][0] = rect_xy2(654, 1350, 775, 1536);
	pos[5][1] = rect_xy2(821, 1350, 945, 1536);
	pos[5][2] = rect_xy2(968, 1350, 1113, 1536);
	pos[5][3] = rect_xy2(1132, 1350, 1265, 1536);
}