
#include "doom.h"

void	put_portal_pixels(t_render *render, int coord, t_xyz text)
{
	Uint32		pixel;

	pixel = ((Uint32*)render->ptx->surface->pixels)
		[(int)text.y * render->ptx->w + (int)text.x];
	if (((pixel >> 24) & 0xFF) < OPAQUE)
		return ;
	((Uint32*)render->surface->pixels)[coord] = pixel;
	((double*)render->surface->userdata)[coord] = text.z;
}

void	draw_portal_texture(t_render *render, t_vline *vline)
{
	t_xyz text;
	double alpha;
	int	coord;

	text.z = vline->z;
	text.x = (vline->alpha * render->wall.tscale.x * vline->z);
	if (text.x >= render->ptx->w || text.x < 0)
		text.x = abs((int)text.x % render->ptx->w);
	text.x = clamp(text.x, 0, render->ptx->w);
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * W + render->x;
		alpha = (vline->y1 - vline->max.ceiling) / vline->line_height;
		text.y = alpha * render->wall.tscale.y;
		if (text.y >= render->ptx->h || text.y < 0)
			text.y = abs((int)text.y % render->ptx->h);
		if (vline->z < ((double*)render->surface->userdata)[coord])
			put_portal_pixels(render, coord, text);
		vline->y1++;
	}
}
