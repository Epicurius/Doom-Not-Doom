/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor&ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:43:50 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/10 12:37:51 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_floor_and_ceiling(t_render *render, t_vline *vline)
{
	if (vline->curr.ceiling > render->ytop)
	{
		vline->height.ceiling = vline->max.ceiling - render->ceiling.head;
		vline->y1 = render->ytop;
		vline->y2 = ft_min(vline->curr.ceiling, render->ybot);
		if (render->ceiling.tx == 0 || TEXTURE_DISABLED)
			vline_monochromic(render, vline, TOP);
		else if (render->ceiling.tx < 0)
			draw_skybox(render, vline, TOP);
		else
			draw_ceiling_texture(render, vline);
	}
	if (vline->curr.floor < render->ybot)
	{
		vline->height.floor = render->floor.feet - vline->max.floor;
		vline->y1 = ft_max(0, vline->curr.floor);
		vline->y2 = render->ybot;
		if (render->floor.tx == 0 || TEXTURE_DISABLED)
			vline_monochromic(render, vline, BOT);
		else if (render->floor.tx < 0)
			draw_skybox(render, vline, BOT);
		else
			draw_floor_texture(render, vline);
	}
}
