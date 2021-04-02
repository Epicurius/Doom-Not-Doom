
#include "doom.h"

void	skybox_wall_vline(t_render *render, t_vline vline, int texture_w)
{
	t_xyz	text;
	double	alpha;
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
			blit_pixel_skybox(render, coord, text, render->s);
		vline.y1++;
	}
}
