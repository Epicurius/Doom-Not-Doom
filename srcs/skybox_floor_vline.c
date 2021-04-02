
#include "doom.h"

void	skybox_floor_vline(t_render *render, t_vline vline)
{
	t_xyz text;
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
			blit_pixel_skybox(render, coord, text, 4);
		vline.y1++;
	}
}
