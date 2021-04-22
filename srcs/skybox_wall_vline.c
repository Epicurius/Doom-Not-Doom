
#include "doom.h"

void	skybox_wall_vline(t_render *render, t_vline vline, int tx)
{
	t_xyz	text;
	double	alpha;
	int		coord;
	int		t_w;

	if (render->skybox[render->s].sv2.z)
		t_w = render->stx[tx].w / render->skybox[render->s].sv2.z;
	else
		t_w = render->stx[tx].w / render->skybox[render->s].cv2.z;
	text.x = (vline.alpha * t_w * vline.z);
	while (text.x >= render->stx[tx].w)
		text.x -= render->stx[tx].w;
	while (text.x < 0)
		text.x += render->stx[tx].w;
	//text.x = ft_clamp(text.x, 0, render->stx[render->s].w);
	while (vline.y1 < vline.y2)
	{
		coord = vline.y1 * W + render->x;
		alpha = (vline.y1 - vline.max.ceiling) / vline.line_height;
		text.y = alpha * render->stx[tx].h;
		while (text.y >= render->stx[tx].h)
			text.y -= render->stx[tx].h;
		while (text.y < 0)
			text.y += render->stx[tx].h;
		blit_pixel_skybox(render, coord, text, tx);
		vline.y1++;
	}
}
