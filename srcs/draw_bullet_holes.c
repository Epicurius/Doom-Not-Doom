
#include "doom.h"

void	put_bh_pixels(t_render *render, int coord, t_xyz text)
{
	Uint32		*pixels;

	if (text.z >= ((double*)render->surface->userdata)[coord])
		return ;
	pixels = render->wtx[48].surface->pixels;
	if (pixels[(int)text.y * render->wtx[48].w + (int)text.x] == 0xFF800080)
		return ;
	((Uint32*)render->surface->pixels)[coord] =
		pixels[(int)text.y * render->wtx[48].w + (int)text.x];
	((double*)render->surface->userdata)[coord] = text.z;
}

void	vline_wall_bh(t_render *render, t_vline *vline, t_sprite bh, int x)
{
	t_xyz text;
	double alpha;
	double pos;
	int coord;

	text.z = vline->z;
	text.x = x;
	pos = bh.pos.y / render->wall.height;
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * W + render->x;
		alpha = (vline->y1 - vline->max.ceiling) / vline->line_height;
		text.y = (alpha - pos) * bh.tscale.y + 0;
		if (text.y >= render->wtx[48].y && text.y < render->wtx[48].h)
			put_bh_pixels(render, coord, text);
		vline->y1++;
	}
}

void	draw_wall_bh(t_render *render, t_vline *vline)
{
	int i = -1;
	t_sprite bh;

	while (++i < render->bh->total)
	{
		bh = render->bh->num[i];
		if (!bh.ready)
			continue ;
		double pos = bh.pos.x / render->wall.width * bh.tscale.x;
		pos *= (render->wall.sv2.z) ? render->wall.sv2.z : render->wall.cv2.z;
		int x = vline->alpha * bh.tscale.x * vline->z + 0 - pos;
		if (x >= render->wtx[48].x && x < render->wtx[48].w)
		{
			vline->y1 = vline->curr.ceiling;
			vline->y2 = vline->curr.floor;
			vline_wall_bh(render, vline, bh, x);
		}
	}
}
