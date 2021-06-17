/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:43:54 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 14:04:05 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_floor_texture(t_render *render, t_vline *vline)
{
	int		coord;
	t_v3	text;
	double	alpha;
	double	divider;
	t_bxpm	*ftx;

	ftx = &render->mtx[render->floor.tx];
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * render->surface->w + render->x;
		alpha = (vline->y1 - vline->max.floor) / vline->height.floor;
		divider = 1 / (NEAR_Z + alpha * vline->zrange);
		text.z = vline->z_near_z * divider;
		text.y = ((vline->texel_nearz.y + alpha * vline->texel_range.y)
				* divider) * render->floor.scale;
		text.x = ((vline->texel_nearz.x + alpha * vline->texel_range.x)
				* divider) * render->floor.scale;
		if (text.y >= ftx->h || text.y < 0)
			text.y = abs((int)text.y % ftx->h);
		if (text.x >= ftx->w || text.x < 0)
			text.x = abs((int)text.x % ftx->w);
		blit_pixel_brightness(render, coord, text, ftx);
		vline->y1++;
	}
}
