/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bullet_holes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:42:50 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/19 17:30:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Draw bullet hole.
 */
static void	vline_wall_bh(t_render *render, t_vline *vline,
	t_wsprite bullet_hole, int x)
{
	t_v3	text;
	int		coord;
	TEMP_DOUBLE	alpha;
	TEMP_DOUBLE	pos;

	text.z = vline->z;
	text.x = x;
	pos = bullet_hole.where.y / render->wall->height;
	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * render->surface->w + render->x;
		alpha = (vline->y1 - vline->max.top) / vline->line_height;
		text.y = (alpha - pos) * bullet_hole.tscale.y + 0;
		if (text.y >= 0 && text.y < 64)
			blit_pixel_opaque(render, coord, text, &render->mtx[0]);
		vline->y1++;
	}
}

/*
 *	Calculate scale and pos of the bullet hole.
 */
void	draw_wall_bh(t_render *render, t_vline *vline)
{
	int			i;
	int			x;
	TEMP_DOUBLE		pos;
	t_wsprite	bullet_hole;

	i = -1;
	while (++i < render->bullet_hole->total)
	{
		bullet_hole = render->bullet_hole->num[i];
		if (!bullet_hole.ready)
			continue ;
		pos = bullet_hole.where.x / render->wall->width * bullet_hole.tscale.x;
		if (render->wall->sv2.z)
			pos *= render->wall->sv2.z;
		else
			pos *= render->wall->cv2.z;
		x = vline->alpha * bullet_hole.tscale.x * vline->z + 0 - pos;
		if (x >= 0 && x < 64)
		{
			vline->y1 = vline->curr.top;
			vline->y2 = vline->curr.bot;
			vline_wall_bh(render, vline, bullet_hole, x);
		}
	}
}
