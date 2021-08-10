/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_neighbor_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:43:59 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/19 10:27:39 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	draw_neighbor_wall2(t_render *render, t_vline *vline)
{
	if (vline->curr_n.ceiling > vline->curr.ceiling)
	{
		vline->y1 = vline->curr.ceiling;
		vline->y2 = vline->curr_n.ceiling;
		if (render->wall.wtx == 0 || TEXTURE_DISABLED)
			vline_monochromic(render, vline, TOP_HALF);
		else if (render->wall.wtx < 0)
			draw_skybox(render, vline, TOP_HALF);
		else
			draw_wall_texture(render, vline);
	}
	if (vline->curr_n.floor < vline->curr.floor)
	{
		vline->y1 = vline->curr_n.floor;
		vline->y2 = vline->curr.floor;
		if (render->wall.wtx == 0 || TEXTURE_DISABLED)
			vline_monochromic(render, vline, BOT_HALF);
		else if (render->wall.wtx < 0)
			draw_skybox(render, vline, BOT_HALF);
		else
			draw_wall_texture(render, vline);
	}
}

void	draw_neighbor_wall(t_render *render, t_vline *vline)
{
	vline->max_n.ceiling = vline->clipped_alpha
		* render->wall.nslope_range.ceiling + render->wall.nslope_v1.ceiling;
	vline->max_n.floor = vline->clipped_alpha
		* render->wall.nslope_range.floor + render->wall.nslope_v1.floor;
	vline->curr_n.ceiling = ft_clamp(vline->max_n.ceiling,
			render->ytop, render->ybot);
	vline->curr_n.floor = ft_clamp(vline->max_n.floor,
			render->ytop, render->ybot);
	draw_neighbor_wall2(render, vline);
	render->ytop = ft_clamp(ft_max(vline->curr_n.ceiling,
				vline->curr.ceiling), render->ytop, render->ybot);
	render->ybot = ft_clamp(ft_min(vline->curr_n.floor,
				vline->curr.floor), render->ytop, render->ybot);
}
