
#include "doom.h"

void	skybox_floor_vline(t_render *render, t_vline vline, int tx)
{
	t_xyz text;
	double alpha;
	int coord;

	while (vline.y1 < vline.y2)
	{
		coord = vline.y1 * W + render->x;
		alpha = vline.start.floor / (double)(vline.y1 - render->player.horizon);
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
		//if (RENDER_DISTANCE == ((double*)render->surface->userdata)[coord])
			blit_pixel_skybox(render, coord, text, tx);
		vline.y1++;
	}
}
