/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:43:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/08 10:43:31 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_ceiling_texture(t_render *render, t_vline *vline)
{
	t_xyz text;
	double alpha;
	double divider;
	int	coord;
	t_bxpm *ctx;

	ctx = &render->mtx[render->ceiling.tx];
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * render->surface->w + render->x;
		alpha = (vline->max.ceiling - vline->y1) / vline->height.ceiling;
		divider = 1 / (NEAR_Z + alpha * vline->zrange);
		text.z = vline->z_near_z * divider;
		text.y = (vline->texel_nearz.y + alpha * vline->texel_range.y)
				* divider;
		text.x = (vline->texel_nearz.x + alpha * vline->texel_range.x)
				* divider;
		text.y *= render->ceiling.scale;
		text.x *= render->ceiling.scale;
		if (text.y >= ctx->h || text.y < 0)
			text.y = abs((int)text.y % ctx->h);
		if (text.x >= ctx->w || text.x < 0)
			text.x = abs((int)text.x % ctx->w);
		blit_pixel_brightness(render, coord, text, ctx);
		vline->y1++;
	}
}
