
#include "doom.h"

void	skybox_wall_vline(t_render *render, t_vline vline, int texture_w)
{
	t_xyz	text;
	double	alpha;
	int	coord;

	text.x = (vline.alpha * texture_w * vline.z);
	while (text.x >= render->stx[render->s].w)
		text.x -= render->stx[render->s].w;
	while (text.x < 0)
		text.x += render->stx[render->s].w;
	//text.x = ft_clamp(text.x, 0, render->stx[render->s].w);
	while (vline.y1 < vline.y2)
	{
		coord = vline.y1 * W + render->x;
		alpha = (vline.y1 - vline.max.ceiling) / vline.line_height;
		text.y = alpha * render->stx[render->s].h;
		while (text.y >= render->stx[render->s].h)
			text.y -= render->stx[render->s].h;
		while (text.y < 0)
			text.y += render->stx[render->s].h;
		blit_pixel_skybox(render, coord, text, render->s);
		vline.y1++;
	}
}
