/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_entity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 12:05:12 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/01 13:37:14 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Calculates the entity projection values.
 */
void	project_entity(t_doom *doom, t_entity *e, t_entity_render *render)
{
	t_v2	size;
	t_v3	dist;
	t_v3	screen;

	dist.x = e->where.x - doom->player.where.x;
	dist.y = e->where.z - doom->player.where.z - doom->player.eyelvl;
	dist.z = e->where.y - doom->player.where.y;
	screen.x = dist.x * doom->player.anglesin - dist.z * doom->player.anglecos;
	screen.z = dist.x * doom->player.anglecos + dist.z * doom->player.anglesin;
	screen.y = dist.y + screen.z * doom->player.pitch;
	screen.x = doom->c.x + screen.x * doom->cam.scale / -screen.z;
	screen.y = doom->c.y + screen.y * doom->cam.scale / -screen.z;
	size.y = doom->c.x * g_entity_data[e->type].scale
		* doom->cam.scale / screen.z;
	size.x = size.y * doom->eframes[e->type].pos[e->state][e->frame][e->angle].w
		/ (double)doom->eframes[e->type].pos[e->state][e->frame][e->angle].h;
	render->z = screen.z;
	render->start = new_point(screen.x - size.x / 2, screen.y - size.y);
	render->end = new_point(screen.x + size.x / 2, screen.y);
	render->clamp_start.x = ft_clamp(render->start.x, 0, doom->surface->w - 1);
	render->clamp_start.y = ft_clamp(render->start.y, 0, doom->surface->h - 1);
	render->clamp_end.x = ft_clamp(render->end.x, 0, doom->surface->w - 1);
	render->clamp_end.y = ft_clamp(render->end.y, 0, doom->surface->h - 1);
	render->xrange = render->end.x - render->start.x;
	render->yrange = render->end.y - render->start.y;
}
