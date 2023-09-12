/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Draw neighbour wall.
 *	The top and bot half if the neighbor floor or ceiling are higher and lower
 *	than the current sectors floor and ceiling.
 */
static void	draw_neighbor_wall2(t_render *render, t_vline *vline)
{
	if (vline->curr_n.top > vline->curr.top)
	{
		vline->y1 = vline->curr.top;
		vline->y2 = vline->curr_n.top;
		if (render->wall->wtx == 0 || TEXTURE_DISABLED)
			vline_monochromic(render, vline, TOP_HALF);
		else if (render->wall->wtx < 0)
			draw_skybox(render, vline, TOP_HALF);
		else
			draw_wall_texture(render, vline);
	}
	if (vline->curr_n.bot < vline->curr.bot)
	{
		vline->y1 = vline->curr_n.bot;
		vline->y2 = vline->curr.bot;
		if (render->wall->wtx == 0 || TEXTURE_DISABLED)
			vline_monochromic(render, vline, BOT_HALF);
		else if (render->wall->wtx < 0)
			draw_skybox(render, vline, BOT_HALF);
		else
			draw_wall_texture(render, vline);
	}
}

/*
 *	Calculate the position of the neighbour wall draw window.
 */
void	draw_neighbor_wall(t_render *render, t_vline *vline)
{
	vline->max_n.top = vline->clipped_alpha
		* render->wall->incl_nrange.top + render->wall->incl_ny1.top;
	vline->max_n.bot = vline->clipped_alpha
		* render->wall->incl_nrange.bot + render->wall->incl_ny1.bot;
	vline->curr_n.top = ft_clamp(vline->max_n.top,
			render->ytop, render->ybot);
	vline->curr_n.bot = ft_clamp(vline->max_n.bot,
			render->ytop, render->ybot);
	draw_neighbor_wall2(render, vline);
	render->ytop = ft_clamp(ft_max(vline->curr_n.top,
				vline->curr.top), render->ytop, render->ybot);
	render->ybot = ft_clamp(ft_min(vline->curr_n.bot,
				vline->curr.bot), render->ytop, render->ybot);
}
