/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:52 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/11 12:08:18 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Draw skybox vertical line floor texture to window surface.
 */
void	skybox_floor_vline(t_render *render, t_vline vline, int tx)
{
	int		coord;
	t_v3	text;
	double	alpha;

	while (vline.y1 < vline.y2)
	{
		coord = vline.y1 * render->surface->w + render->x;
		alpha = vline.start.floor
			/ (double)(vline.y1 - render->player.horizon);
		text.y = (alpha * vline.texel.y + (1.0 - alpha) * 5)
			* render->stx[tx].h / 10;
		text.x = (alpha * vline.texel.x + (1.0 - alpha) * 5)
			* render->stx[tx].w / 10;
		if (text.y >= render->stx[tx].h || text.y < 0)
			text.y = abs((int)text.y % render->stx[4].h);
		if (text.x >= render->stx[tx].w || text.x < 0)
			text.x = abs((int)text.x % render->stx[4].w);
		text.y = render->stx[tx].h - text.y;
		text.x = render->stx[tx].w - text.x;
		blit_pixel_skybox(render, coord, text, tx);
		vline.y1++;
	}
}
