
#include "doom.h"

void	put_wall_pixels(t_render *render, int coord, t_xyz text, t_texture *wtx)
{
	Uint32		*pixels;

	pixels = wtx->surface->pixels;
	((Uint32*)render->surface->pixels)[coord] = 
	brightness(pixels[(int)text.y * wtx->w + (int)text.x], render->light);
	((double*)render->surface->userdata)[coord] = text.z;
}

void	draw_wall_texture(t_render *render, t_vline *vline)
{
	t_xyz text;
	double alpha;
	int	coord;
	t_texture *wtx = &render->wtx[render->wall.wtx];

	text.z = vline->z;
	text.x = (vline->alpha * render->wall.tscale.x * vline->z);

	if (text.x >= wtx->w || text.x < 0)
		text.x = abs((int)text.x % wtx->w);
	//text.x = clamp(text.x, 0, wtx->w);
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * W + render->x;
		alpha = (vline->y1 - vline->max.ceiling) / vline->line_height;
		crosshair_position(render, vline, alpha);
		text.y = alpha * render->wall.tscale.y;

		if (text.y >= wtx->h || text.y < 0)
			text.y = abs((int)text.y % wtx->h);
		if (text.z < ((double*)render->surface->userdata)[coord])
			put_wall_pixels(render, coord, text, wtx);
		vline->y1++;
	}
}
