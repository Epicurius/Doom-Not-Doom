/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox_ceiling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:48 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/23 11:16:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Draw skybox vertical line ceiling texture to window surface.
 */
void	skybox_ceiling_vline(t_render *render, t_vline vline, int tx)
{
	int		coord;
	t_v3	text;
	float	alpha;

	while (vline.y1 <= vline.y2)
	{
		coord = vline.y1 * render->surface->w + render->x;
		alpha = vline.start.top
			/ (float)(vline.y1 - render->player->horizon);
		text.y = (alpha * vline.texel.y + (1.0 - alpha) * 5)
			* render->stx[tx].h / 10;
		text.x = (alpha * vline.texel.x + (1.0 - alpha) * 5)
			* render->stx[tx].w / 10;
		if (text.y >= render->stx[tx].w || text.y < 0)
			text.y = abs((int)text.y % render->stx[tx].w);
		if (text.x >= render->stx[tx].w || text.x < 0)
			text.x = abs((int)text.x % render->stx[tx].w);
		text.x = render->stx[tx].w - text.x;
		blit_pixel_skybox(render, coord, text, tx);
		vline.y1++;
	}
}
