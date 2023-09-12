/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Draw skybox vertical line wall texture to window surface.
 */
void	skybox_wall_vline(t_render *render, t_vline vline, int tx)
{
	int		coord;
	t_v3	text;
	float	alpha;

	if (render->skybox[render->s].sv2.z)
		coord = render->stx[tx].w / render->skybox[render->s].sv2.z;
	else
		coord = render->stx[tx].w / render->skybox[render->s].cv2.z;
	text.x = (vline.alpha * coord * vline.z);
	if (text.x >= render->stx[tx].w || text.x < 0)
		text.x = abs((int)text.x % render->stx[tx].w);
	while (vline.y1 < vline.y2)
	{
		coord = vline.y1 * render->surface->w + render->x;
		alpha = (vline.y1 - vline.max.top) / vline.line_height;
		text.y = alpha * render->stx[tx].h;
		if (text.y >= render->stx[tx].h || text.y < 0)
			text.y = abs((int)text.y % render->stx[tx].h);
		blit_pixel_skybox(render, coord, text, tx);
		vline.y1++;
	}
}
