
#include "doom.h"

void	put_skybox_wall_pixels(t_render *render, int coord, t_v2 text)
{
	Uint32		*pixels;

	pixels = render->stx[render->s].surface->pixels;
	((Uint32*)render->surface->pixels)[coord] =
		pixels[(int)text.y * 2048 + (int)text.x];
}

void	skybox_wall_vline(t_render *render, t_vline vline, int texture_w)
{
	t_v2 text;
	double alpha;
	int	coord;

	text.x = (vline.alpha * texture_w * vline.z);
	while (text.x >= 2048)
		text.x -= 2048;
	while (text.x < 0)
		text.x += 2048;
	text.x = clamp(text.x, 0, 2048);
	while (vline.y1 < vline.y2)
	{
		coord = vline.y1 * W + render->x;
		alpha = (vline.y1 - vline.max.ceiling) / vline.line_height;
		text.y = alpha * 2048;
		while (text.y >= 2048)
			text.y -= 2048;
		while (text.y < 0)
			text.y += 2048;
		if (RENDER_DISTANCE == ((double*)render->surface->userdata)[coord])
			put_skybox_wall_pixels(render, coord, text);
		vline.y1++;
	}
}
