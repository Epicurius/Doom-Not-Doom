
#include "doom.h"

void	put_bh_pixels(t_render *render, int coord, t_xyz text)
{
	uint32_t	clr;
	unsigned short	pix;

	pix = render->mtx[0].pix[(int)text.y * 128 + (int)text.x];
	clr = render->mtx[0].clr[pix];
	if (clr == 0x800080)
		return ;
	((Uint32*)render->surface->pixels)[coord] = clr;
	((double*)render->surface->userdata)[coord] = text.z;
}

void	vline_wall_bh(t_render *render, t_vline *vline, t_game_wsprite bh, int x)
{
	t_xyz text;
	double alpha;
	double pos;
	int coord;

	text.z = vline->z;
	text.x = x;
	pos = bh.where.y / render->wall.height;
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * render->surface->w + render->x;
		alpha = (vline->y1 - vline->max.ceiling) / vline->line_height;
		text.y = (alpha - pos) * bh.tscale.y + 0;
		if (text.y >= 0 && text.y < 128)
			put_bh_pixels(render, coord, text);
		vline->y1++;
	}
}

void	draw_wall_bh(t_render *render, t_vline *vline)
{
	int i = -1;
	t_game_wsprite bh;

	if (!ENABLE_BH)
		return ;
	while (++i < render->bh->total)
	{
		bh = render->bh->num[i];
		if (!bh.ready)
			continue ;
		double pos = bh.where.x / render->wall.width * bh.tscale.x;
		pos *= (render->wall.sv2.z) ? render->wall.sv2.z : render->wall.cv2.z;
		int x = vline->alpha * bh.tscale.x * vline->z + 0 - pos;
		if (x >= 0 && x < 128)
		{
			vline->y1 = vline->curr.ceiling;
			vline->y2 = vline->curr.floor;
			vline_wall_bh(render, vline, bh, x);
		}
	}
}
