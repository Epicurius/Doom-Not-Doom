
#include "doom.h"

void	put_wsprite_pixels(t_render *render, int coord, t_xyz text, t_texture *wstx)
{
	Uint32		*pixels;

	if (text.z >= ((double*)render->surface->userdata)[coord])
		return ;
	pixels = wstx->surface->pixels;
	//if (pixels[(int)text.y * wstx->surface->w + (int)text.x] == 0xFF800080)
	if (((pixels[(int)text.y * wstx->surface->w + (int)text.x] >> 24) & 0xFF) < OPAQUE)
		return ;
	((Uint32*)render->surface->pixels)[coord] =
		pixels[(int)text.y * wstx->surface->w + (int)text.x];
	((double*)render->surface->userdata)[coord] = text.z;
}

void	vline_wsprite(t_render *render, t_vline *vline, t_sprite sprite, int x)
{
	t_xyz text;
	double alpha;
	double pos;
	int coord;

	text.x = x;
	text.z = vline->z;
	pos = sprite.pos.y / render->wall.height;
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * W + render->x;
		alpha = (vline->y1 - vline->max.ceiling) / vline->line_height;
		text.y = (alpha - pos) * sprite.tscale.y + sprite.y;
		//if (text.y >= render->wtx[sprite.t].y && text.y < render->wtx[sprite.t].h)
		if (text.y > sprite.y && text.y < (sprite.y + render->wtx[sprite.t].h))
			put_wsprite_pixels(render, coord, text, &render->wtx[sprite.t]);
		vline->y1++;
	}
}

void	draw_wsprites(t_render *render, t_vline *vline)
{
	int i = -1;
	t_sprite sprite;

	while (++i < render->wsprite->total)
	{
		sprite = render->wsprite->num[i];
		if (!sprite.ready)
			continue ;
		double pos = sprite.pos.x / render->wall.width * sprite.tscale.x;
		pos *= (render->wall.sv2.z) ? render->wall.sv2.z : render->wall.cv2.z;
		int x = vline->alpha * sprite.tscale.x * vline->z + sprite.x - pos;
		//if (x >= render->wtx[sprite.t].x && x < render->wtx[sprite.t].w)
		if (x > sprite.x && x < (sprite.x + render->wtx[sprite.t].w))
		{
			vline->y1 = vline->curr.ceiling;
			vline->y2 = vline->curr.floor;
			vline_wsprite(render, vline, sprite, x);
		}
	}
}
