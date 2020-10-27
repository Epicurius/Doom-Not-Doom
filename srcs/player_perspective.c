/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_perspective.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:08:23 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/27 17:20:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		player_perspective_tranformation(t_scale *persp, t_xyz t[2])
{
    /* Do perspective transformation */
	persp->xscale1 = (HORI_FOV) / t[0].z;
	persp->yscale1 = (VERT_FOV) / t[0].z;
	persp->xscale2 = (HORI_FOV) / t[1].z;
	persp->yscale2 = (VERT_FOV) / t[1].z;
	persp->x1 = W / 2 - (int)(t[0].x * persp->xscale1);
	persp->x2 = W / 2 - (int)(t[1].x * persp->xscale2);
}
