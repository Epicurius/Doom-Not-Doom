/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Draw vertical line portal texture to window surface.
 */
static void	draw_portal_solid(t_render *render, t_vline *vline)
{
	t_v3	text;
	float	alpha;
	int		coord;
	t_bxpm	*ptx;

	ptx = &render->mtx[render->wall->ptx];
	text.z = vline->z;
	text.x = (vline->alpha * render->wall->clip_scale.x * vline->z);
	if (text.x >= ptx->w || text.x < 0)
		text.x = abs((int)text.x % ptx->w);
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * render->surface->w + render->x;
		alpha = (vline->y1 - vline->max.top) / vline->line_height;
		text.y = alpha * render->wall->clip_scale.y;
		if (text.y >= ptx->h || text.y < 0)
			text.y = abs((int)text.y % ptx->h);
		blit_pixel_opaque(render, coord, text, ptx);
		vline->y1++;
	}
}

/*
 *	Draw portal texture and wall sprites.
 */
void	draw_portal_texture(t_render *render, t_vline *vline)
{
	vline->y1 = render->ytop;
	vline->y2 = render->ybot;
	draw_portal_solid(render, vline);
	vline->y1 = render->ytop;
	vline->y2 = render->ybot;
	draw_wsprites(render, vline);
}
