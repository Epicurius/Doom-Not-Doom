
#include "doom.h"

void	draw_wall_texture(t_render *render, t_vline *vline)
{
	t_xyz text;
	double alpha;
	int	coord;
	t_bxpm *wtx;

	wtx = &render->mtx[render->wall.wtx];
	text.z = vline->z;
	text.x = (vline->alpha * render->wall.tscale.x * vline->z);
	if (text.x >= wtx->w || text.x < 0)
		text.x = abs((int)text.x % wtx->w);
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * W + render->x;
		alpha = (vline->y1 - vline->max.ceiling) / vline->line_height;
		crosshair_position(render, vline, alpha);
		text.y = alpha * render->wall.tscale.y;

		if (text.y >= wtx->h || text.y < 0)
			text.y = abs((int)text.y % wtx->h);
		//if (text.z < ((double*)render->surface->userdata)[coord])
			blit_pixel_brightness(render, coord, text, wtx);
		vline->y1++;
	}
}
