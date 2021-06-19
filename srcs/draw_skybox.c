/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:44:11 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/19 16:43:25 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	skybox_limits(t_render *render, t_vline *vline,
	int side, int *limit)
{
	if (side == TOP)
	{
		limit[0] = render->ytop;
		limit[1] = vline->curr.ceiling;
	}
	else if (side == BOT)
	{
		limit[0] = vline->curr.floor;
		limit[1] = render->ybot;
	}
	else if (side == SIDES)
	{
		limit[0] = vline->curr.ceiling;
		limit[1] = vline->curr.floor;
	}
	else if (side == TOP_HALF)
	{
		limit[0] = vline->curr.ceiling;
		limit[1] = vline->curr_n.ceiling;
	}
	else if (side == BOT_HALF)
	{
		limit[0] = vline->curr_n.floor;
		limit[1] = vline->curr.floor;
	}
}

static void	draw_skybox_vline(t_render *render, t_vline skybox, int *limit)
{
	int	i;

	i = (render->wall.wtx + 1) * (-6);
	if (limit[0] < skybox.curr.ceiling)
	{
		skybox.y1 = limit[0];
		skybox.y2 = ft_min(skybox.curr.ceiling, limit[1]);
		skybox_ceiling_vline(render, skybox, i + 4);
	}
	if (skybox.curr.ceiling < limit[1])
	{	
		skybox.y1 = ft_max(limit[0], skybox.curr.ceiling);
		skybox.y2 = ft_min(skybox.curr.floor, limit[1]);
		skybox_wall_vline(render, skybox, i + render->s);
	}
	if (skybox.curr.floor < limit[1])
	{
		skybox.y1 = ft_max(limit[0], skybox.curr.floor);
		skybox.y2 = limit[1];
		skybox_floor_vline(render, skybox, i + 5);
	}
}

static void	compute_skybox_vline_data(t_render *render, t_vline *vline, int i)
{
	t_wall	w;

	w = render->skybox[i];
	vline->alpha = (render->x - w.x1) / w.xrange;
	vline->clipped_alpha = (render->x - w.cx1) / (w.cx2 - w.cx1);
	vline->z = 1.0 / ((1.0 - vline->alpha) / w.sv1.z + vline->alpha / w.sv2.z);
	vline->divider = 1 / (w.sv2.z + vline->alpha * w.zrange);
	vline->z = w.zcomb * vline->divider;
	vline->texel.x = (w.x0z1 + vline->alpha * w.xzrange) * vline->divider;
	vline->texel.y = (w.y0z1 + vline->alpha * w.yzrange) * vline->divider;
	vline->max.ceiling = vline->clipped_alpha
		* w.slope_range.ceiling + w.slope_v1.ceiling;
	vline->curr.ceiling = ft_clamp(vline->max.ceiling, render->ytop,
			render->ybot);
	vline->max.floor = vline->clipped_alpha
		* w.slope_range.floor + w.slope_v1.floor;
	vline->curr.floor = ft_clamp(vline->max.floor, render->ytop, render->ybot);
	vline->start.ceiling = vline->max.ceiling - render->player.horizon;
	vline->start.floor = vline->max.floor - render->player.horizon;
	vline->line_height
		= (vline->clipped_alpha * w.slope_range.floor + w.slope_v1.floor)
		- (vline->clipped_alpha * w.slope_range.ceiling + w.slope_v1.ceiling);
}

void	draw_skybox(t_render *render, t_vline *vline, int side)
{
	int			i;
	int			limit[2];
	t_vline		skybox;

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
