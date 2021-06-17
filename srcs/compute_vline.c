/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_vline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 15:06:06 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 15:06:33 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	compute_vline_data(t_render *render, t_wall wall, t_vline *vline)
{
	vline->alpha = (render->x - wall.x1) / wall.xrange;
	vline->clipped_alpha = (render->x - wall.cx1) / (wall.cx2 - wall.cx1);
	vline->divider = 1 / (wall.sv2.z + vline->alpha * wall.zrange);
	vline->z = wall.zcomb * vline->divider;
	vline->z_near_z = vline->z * NEAR_Z;
	vline->max.ceiling = vline->clipped_alpha * wall.range.ceiling + wall.s1.ceiling;
	vline->curr.ceiling = ft_clamp(vline->max.ceiling, render->ytop, render->ybot);
	vline->max.floor = vline->clipped_alpha * wall.range.floor + wall.s1.floor;
	vline->curr.floor = ft_clamp(vline->max.floor, render->ytop, render->ybot);
	vline->real_floor = vline->clipped_alpha * wall.range.f + wall.s1.f;
	vline->real_ceiling = vline->clipped_alpha * wall.range.c + wall.s1.c;
	vline->line_height = vline->real_floor - vline->real_ceiling;
}

void	compute_vline_texels(t_render *render, t_wall wall, t_vline *vline)
{
	t_v2	camera_z;

	camera_z.x = render->player.where.x * vline->z;
	camera_z.y = render->player.where.y * vline->z;
	vline->texel.x = (wall.x0z1 + vline->alpha * wall.xzrange) * vline->divider;
	vline->texel.y = (wall.y0z1 + vline->alpha * wall.yzrange) * vline->divider;
	vline->texel_nearz.x = vline->texel.x * NEAR_Z;
	vline->texel_nearz.y = vline->texel.y * NEAR_Z;
	vline->texel_range.x = camera_z.x - vline->texel_nearz.x;
	vline->texel_range.y = camera_z.y - vline->texel_nearz.y;
	vline->zrange = vline->z - NEAR_Z;
}
