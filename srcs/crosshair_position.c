/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:42:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/20 12:54:09 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//		ft_printf("%d\n", render->wall.id);
void	crosshair_position(t_render *render, t_vline *vline, double alpha)
{
	t_wall		*wall;
	t_wsprite	*bh;

	if (render->player.shooting && render->x == render->surface->w / 2
		&& vline->y1 == render->surface->h / 2)
	{
		wall = &render->wall;
		if (render->bh->curr >= MAX_BH)
			render->bh->curr = 0;
		bh = &render->bh->num[render->bh->curr];
		bh->where.x = (vline->alpha / wall->sv2.z)
			/ ((1 - vline->alpha) / wall->sv1.z + vline->alpha / wall->sv2.z)
			* wall->width;
		bh->where.y = alpha * wall->height;
		bh->where.x -= 0.5;
		bh->where.y -= 0.5;
		bh->ready = 0;
		render->bh->curr += 1;
		if (render->bh->total < MAX_BH)
			render->bh->total += 1;
	}
}
