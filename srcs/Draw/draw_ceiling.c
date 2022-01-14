/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/08 10:43:29 nneronin
 * Updated: 2021/09/23 11:16:08 nneronin
 */

#include "doom.h"

/*
 *	Draw veretical line ceiling texture to window surface.
 *	With brightness.
 */
void	draw_ceiling_texture(t_render *render, t_vline *vline)
{
	int		coord;
	t_v3	text;
	float	alpha;
	float	divider;
	t_bxpm	*ctx;

	ctx = &render->mtx[render->ceiling->tx];
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * render->surface->w + render->x;
		alpha = (vline->max.top - vline->y1) / vline->height.top;
		divider = 1 / (NEAR_Z + alpha * vline->zrange);
		text.z = vline->z_near_z * divider;
		text.y = ((vline->texel_nearz.y + alpha * vline->texel_range.y)
				* divider) * render->ceiling->scale;
		text.x = ((vline->texel_nearz.x + alpha * vline->texel_range.x)
				* divider) * render->ceiling->scale;
		if (text.y >= ctx->h || text.y < 0)
			text.y = abs((int)text.y % ctx->h);
		if (text.x >= ctx->w || text.x < 0)
			text.x = abs((int)text.x % ctx->w);
		blit_pixel_brightness(render, coord, text, ctx);
		vline->y1++;
	}
}
