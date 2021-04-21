
#include "doom.h"
/*
void	draw_portal_texture(t_render *render, t_vline *vline)
{
	t_xyz text;
	double alpha;
	int	coord;
	t_texture *ptx;

	ptx = &render->wtx[1];
	text.z = vline->z;
	text.x = (vline->alpha * render->wall.tscale.x * vline->z);
	if (text.x >= ptx->w || text.x < 0)
		text.x = abs((int)text.x % ptx->w);
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * W + render->x;
		alpha = (vline->y1 - vline->max.ceiling) / vline->line_height;
		text.y = alpha * render->wall.tscale.y;

		if (text.y >= ptx->h || text.y < 0)
			text.y = abs((int)text.y % ptx->h);
		if (vline->z < ((double*)render->surface->userdata)[coord])
			blit_pixel_opaque(render, coord, text, ptx);
		vline->y1++;
	}
}*/
