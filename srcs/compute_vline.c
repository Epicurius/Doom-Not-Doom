/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_vline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 15:06:06 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/18 14:13:28 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Calculates the vertical line dimensions for drawing.
 */
void	compute_vline_data(t_render *render, t_wall *wall, t_vline *vline)
{
	vline->alpha = (render->x - wall->x1) / wall->xrange;
	vline->clipped_alpha = (render->x - wall->cx1) / (wall->cx2 - wall->cx1);
	vline->divider = 1 / (wall->sv2.z + vline->alpha * wall->zrange);
	vline->z = wall->zcomb * vline->divider;
	vline->z_near_z = vline->z * NEAR_Z;
	vline->max.ceiling = vline->clipped_alpha
		* wall->incl_range.ceiling + wall->incl_y1.ceiling;
	vline->max.floor = vline->clipped_alpha
		* wall->incl_range.floor + wall->incl_y1.floor;
	vline->curr.ceiling = ft_clamp(vline->max.ceiling,
			render->ytop, render->ybot);
	vline->curr.floor = ft_clamp(vline->max.floor, render->ytop, render->ybot);
	vline->stat_y.floor = vline->clipped_alpha
		* wall->stat_range.floor + wall->stat_y1.floor;
	vline->stat_y.ceiling = vline->clipped_alpha
		* wall->stat_range.ceiling + wall->stat_y1.ceiling;
	vline->line_height = vline->stat_y.floor - vline->stat_y.ceiling;
}

/*
 *	Calculates vertical line texture position.
 */
void	compute_vline_texels(t_render *render, t_wall *wall, t_vline *vline)
{
	t_v2	camera_z;

	camera_z.x = render->player->where.x * vline->z;
	camera_z.y = render->player->where.y * vline->z;
	vline->texel.x = (wall->x1z2 + vline->alpha * wall->xzrange)
		* vline->divider;
	vline->texel.y = (wall->y1z2 + vline->alpha * wall->yzrange)
		* vline->divider;
	vline->texel_nearz.x = vline->texel.x * NEAR_Z;
	vline->texel_nearz.y = vline->texel.y * NEAR_Z;
	vline->texel_range.x = camera_z.x - vline->texel_nearz.x;
	vline->texel_range.y = camera_z.y - vline->texel_nearz.y;
	vline->zrange = vline->z - NEAR_Z;
}
