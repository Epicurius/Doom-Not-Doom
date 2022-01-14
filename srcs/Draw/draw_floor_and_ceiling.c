/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/08 10:43:50 nneronin
 * Updated: 2021/09/19 13:22:09 nneronin
 */

#include "doom.h"

/*
 *	Calls draw floor adn/or ceiling depending if there are visible
 *	on the current vertical line.
 */
void	draw_floor_and_ceiling(t_render *render, t_vline *vline)
{
	if (vline->curr.top > render->ytop)
	{
		vline->height.top = vline->max.top - render->ceiling->ppos;
		vline->y1 = render->ytop;
		vline->y2 = ft_min(vline->curr.top, render->ybot);
		if (render->ceiling->tx == 0 || TEXTURE_DISABLED)
			vline_monochromic(render, vline, TOP);
		else if (render->ceiling->tx < 0)
			draw_skybox(render, vline, TOP);
		else
			draw_ceiling_texture(render, vline);
	}
	if (vline->curr.bot < render->ybot)
	{
		vline->height.bot = render->floor->ppos - vline->max.bot;
		vline->y1 = ft_max(0, vline->curr.bot);
		vline->y2 = render->ybot;
		if (render->floor->tx == 0 || TEXTURE_DISABLED)
			vline_monochromic(render, vline, BOT);
		else if (render->floor->tx < 0)
			draw_skybox(render, vline, BOT);
		else
			draw_floor_texture(render, vline);
	}
}
