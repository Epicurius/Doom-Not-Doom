/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/08 10:44:15 nneronin
 * Updated: 2021/09/23 11:16:08 nneronin
 */

#include "doom.h"

/*
 *	Draw vertical line wall texture to window surface.
 *	With brightness.
 *	And check bullet hole creation.
 */
void	draw_wall_texture(t_render *render, t_vline *vline)
{
	t_v3	text;
	float	alpha;
	int		coord;
	t_bxpm	*wtx;

	wtx = &render->mtx[render->wall->wtx];
	text.z = vline->z;
	text.x = (vline->alpha * render->wall->clip_scale.x * vline->z);
	if (text.x >= wtx->w || text.x < 0)
		text.x = abs((int)text.x % wtx->w);
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * render->surface->w + render->x;
		alpha = (vline->y1 - vline->stat_y.top) / vline->line_height;
		crosshair_position(render, vline, alpha, coord);
		text.y = alpha * render->wall->clip_scale.y;
		if (text.y >= wtx->h || text.y < 0)
			text.y = abs((int)text.y % wtx->h);
		blit_pixel_brightness(render, coord, text, wtx);
		vline->y1++;
	}
}
