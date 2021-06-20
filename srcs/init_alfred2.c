/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_alfred2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:42:57 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/20 11:27:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	move_pos_alfred2(t_rect **pos)
{
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
