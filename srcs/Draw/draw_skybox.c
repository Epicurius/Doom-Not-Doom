/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Calculate the skybox floor & ceiling.
 *	So that there is an affect of hight compared non skybox sectors.
 */
static void	skybox_limits(t_render *render, t_vline *vline,
	int side, int *limit)
{
	if (side == TOP)
	{
		limit[0] = render->ytop;
		limit[1] = vline->curr.top;
	}
	else if (side == BOT)
	{
		limit[0] = vline->curr.bot;
		limit[1] = render->ybot;
	}
	else if (side == SIDES)
	{
		limit[0] = vline->curr.top;
		limit[1] = vline->curr.bot;
	}
	else if (side == TOP_HALF)
	{
		limit[0] = vline->curr.top;
		limit[1] = vline->curr_n.top;
	}
	else
	{
		limit[0] = vline->curr_n.bot;
		limit[1] = vline->curr.bot;
	}
}

/*
 *	Depending on y axis draw skybox floor, wall or ceiling.
 *	skybox.y1 = ft_max(limit[0], skybox.curr.bot) + 1;
 */
static void	draw_skybox_vline(t_render *render, t_vline skybox, int *limit)
{
	int	i;

	i = -((render->wall->wtx + 1) * 6);
	if (limit[0] < skybox.curr.top)
	{
		skybox.y1 = limit[0];
		skybox.y2 = ft_min(skybox.curr.top, limit[1]);
		skybox_plane_vline(render, skybox, skybox.start.top, i + 4);
	}
	if (skybox.curr.top < limit[1])
	{	
		skybox.y1 = ft_max(limit[0], skybox.curr.top);
		skybox.y2 = ft_min(skybox.curr.bot, limit[1]);
		skybox_wall_vline(render, skybox, i + render->s);
	}
	if (skybox.curr.bot < limit[1])
	{
		skybox.y1 = ft_max(limit[0], skybox.curr.bot) + 1;
		skybox.y2 = limit[1];
		skybox_plane_vline(render, skybox, skybox.start.bot, i + 5);
	}
}

/*
 * Calculate skybox vertical line projection values.
 */
static void	compute_skybox_vline_data(t_render *render, t_vline *vline, int i)
{
	t_wall	w;

	w = render->skybox[i];
	vline->alpha = (render->x - w.x1) / w.xrange;
	vline->clipped_alpha = (render->x - w.cx1) / (w.cx2 - w.cx1);
	vline->divider = 1 / (w.sv2.z + vline->alpha * w.zrange);
	vline->z = w.zcomb * vline->divider;
	vline->texel.x = (w.x1z2 + vline->alpha * w.xzrange) * vline->divider;
	vline->texel.y = (w.y1z2 + vline->alpha * w.yzrange) * vline->divider;
	vline->max.top = vline->clipped_alpha
		* w.incl_range.top + w.incl_y1.top;
	vline->curr.top = ft_clamp(vline->max.top, render->ytop,
			render->ybot);
	vline->max.bot = vline->clipped_alpha
		* w.incl_range.bot + w.incl_y1.bot;
	vline->curr.bot = ft_clamp(vline->max.bot, render->ytop, render->ybot);
	vline->start.top = vline->max.top - render->player->horizon;
	vline->start.bot = vline->max.bot - render->player->horizon;
	vline->line_height
		= (vline->clipped_alpha * w.incl_range.bot + w.incl_y1.bot)
		- (vline->clipped_alpha * w.incl_range.top + w.incl_y1.top);
}

/*
 *	Loop all of the skybox walls and if visible draw them.
 */
void	draw_skybox(t_render *render, t_vline *vline, int side)
{
	int			i;
	int			limit[2];
	t_vline		skybox = {0};

	i = -1;
	while (++i < 4)
	{
		if (!render->skybox[i].visible)
			continue ;
		if (render->skybox[i].cx1 >= render->skybox[i].cx2
			|| render->skybox[i].cx1 > render->x
			|| render->skybox[i].cx2 < render->x)
			continue ;
		render->s = i;
		compute_skybox_vline_data(render, &skybox, i);
		skybox_limits(render, vline, side, limit);
		draw_skybox_vline(render, skybox, limit);
	}
}
