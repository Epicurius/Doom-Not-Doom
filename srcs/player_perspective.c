/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_perspective.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:08:23 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/10 17:57:46 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		player_perspective_tranformation(t_scale *viewpoint)
{
    /* Do perspective transformation */
	viewpoint->xscale1 = (HORI_FOV) / viewpoint->edges[0].y;
	viewpoint->yscale1 = (VERT_FOV) / viewpoint->edges[0].y;
	viewpoint->xscale2 = (HORI_FOV) / viewpoint->edges[1].y;
	viewpoint->yscale2 = (VERT_FOV) / viewpoint->edges[1].y;
	viewpoint->x1 = W / 2 - (int)(viewpoint->edges[0].x * viewpoint->xscale1);
	viewpoint->x2 = W / 2 - (int)(viewpoint->edges[1].x * viewpoint->xscale2);
}
