/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_perspective.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:08:23 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/22 16:43:47 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		player_perspective_tranformation(t_scale *persp, t_xyz t[2])
{
    /* Do perspective transformation */
	persp->xscale1 = (W * HORI_FOV) / t[0].z;
	persp->yscale1 = (H * VERT_FOV) / t[0].z;
	persp->xscale2 = (W * HORI_FOV) / t[1].z;
	persp->yscale2 = (H * VERT_FOV) / t[1].z;
	persp->x1 = W / 2 - (int)(t[0].x * persp->xscale1);
	persp->x2 = W / 2 - (int)(t[1].x * persp->xscale2);
}
