
#include "doom.h"

void	put_skybox_floor_pixels(t_render *render, int coord, t_v2 text)
{
	Uint32		*pixels;

	pixels = render->stx[4].surface->pixels;
	//if (text.x >= 0 && text.x < 2048 && text.y >= 0 && text.y < 2048)
	//{
		((Uint32*)render->surface->pixels)[coord] =
			pixels[(int)text.y * 2048 + (int)text.x];
	//}
}

void	skybox_floor_vline(t_render *render, t_vline vline)
{
	t_v2 text;
	double alpha;
	int coord;

	while (vline.y1 < vline.y2)
	{
		coord = vline.y1 * W + render->x;
		alpha = vline.start.floor / (double)(vline.y1 - render->player.horizon);
		text.y = (alpha * vline.texel.y + (1.0 - alpha) * 5) * 2048 / 10;
		text.x = (alpha * vline.texel.x + (1.0 - alpha) * 5) * 2048 / 10;
		if (text.y >= 2048 || text.y < 0)
			text.y = abs((int)text.y % 2048);
		if (text.x >= 2048 || text.x < 0)
			text.x = abs((int)text.x % 2048);
		text.y = 2048 - text.y;
		text.x = 2048 - text.x;
		if (RENDER_DISTANCE == ((double*)render->surface->userdata)[coord])
			put_skybox_floor_pixels(render, coord, text);
		vline.y1++;
	}
}
