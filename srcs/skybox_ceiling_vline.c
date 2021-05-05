
#include "doom.h"

void	skybox_ceiling_vline(t_render *render, t_vline vline, int tx)
{
	t_xyz text;
	double alpha;
	int coord;

	while (vline.y1 <= vline.y2)
	{
		coord = vline.y1 * render->surface->w + render->x;
		alpha = vline.start.ceiling / (double)(vline.y1 - render->player.horizon);
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
