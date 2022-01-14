/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/08 10:53:52 nneronin
 * Updated: 2021/12/18 13:04:53 nneronin
 */

#include "doom.h"

/*
 *	Draw skybox vertical line floor or ceiling texture to window surface.
 */
void	skybox_plane_vline(t_render *render, t_vline vline, float start, int tx)
{
	int		coord;
	t_v3	text;
	float	alpha;
	t_v3	stx;

	stx.x = render->stx[tx].w / 10;
	stx.y = render->stx[tx].h / 10;
	while (vline.y1 < vline.y2)
	{
		coord = vline.y1 * render->surface->w + render->x;
		alpha = start / (vline.y1 - render->player->horizon);
		text.x = (alpha * vline.texel.x + (1.0 - alpha) * 5) * stx.x;
		text.y = (alpha * vline.texel.y + (1.0 - alpha) * 5) * stx.y;
		if (text.y >= render->stx[tx].h || text.y < 0)
			text.y = abs((int)text.y % render->stx[tx].h);
		if (text.x >= render->stx[tx].w || text.x < 0)
			text.x = abs((int)text.x % render->stx[tx].w);
		blit_pixel_skybox(render, coord, text, tx);
		vline.y1++;
	}
}
