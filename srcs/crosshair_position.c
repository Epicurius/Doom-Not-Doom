/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:42:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/21 10:13:23 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	debug(t_render *render, t_wall *wall)
{
	ft_printf("{CLR:204}Wall:\t%d Sector: %d Neighbour: %d\n", wall->id,
		wall->sect, wall->n);
	ft_printf("Player:\t%d [%.1f][%.1f][%.1f]{RESET}\n",
		render->player.sector, render->player.where.x,
		render->player.where.y, render->player.where.z);
}

void	crosshair_position(t_render *render, t_vline *vline, double alpha)
{
	t_wall		*wall;
	t_wsprite	*bh;

	if (render->player.action == SHOOTING && render->x == render->surface->w / 2
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
		if (render->player.debug)
			debug(render, wall);
	}
}
