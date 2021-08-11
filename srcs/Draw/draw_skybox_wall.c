/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:56 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/11 12:08:14 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Draw skybox vertical line wall texture to window surface.
 */
void	skybox_wall_vline(t_render *render, t_vline vline, int tx)
{
	int		coord;
	t_v3	text;
	double	alpha;

	if (render->skybox[render->s].sv2.z)
		coord = render->stx[tx].w / render->skybox[render->s].sv2.z;
	else
		coord = render->stx[tx].w / render->skybox[render->s].cv2.z;
	text.x = (vline.alpha * coord * vline.z);
	while (text.x >= render->stx[tx].w)
		text.x -= render->stx[tx].w;
	while (text.x < 0)
		text.x += render->stx[tx].w;
	while (vline.y1 < vline.y2)
	{
		coord = vline.y1 * render->surface->w + render->x;
		alpha = (vline.y1 - vline.max.ceiling) / vline.line_height;
		text.y = alpha * render->stx[tx].h;
		while (text.y >= render->stx[tx].h)
			text.y -= render->stx[tx].h;
		while (text.y < 0)
			text.y += render->stx[tx].h;
		blit_pixel_skybox(render, coord, text, tx);
		vline.y1++;
	}
}
