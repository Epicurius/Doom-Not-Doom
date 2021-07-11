/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_entity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 12:05:12 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/11 14:35:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	project_entity(t_doom *doom, t_entity *entity, t_entity_render *render)
{
	t_point	size;
	t_v3	dist;
	t_v3	screen;

	dist.x = entity->where.x - doom->player.where.x;
	dist.y = entity->where.z - doom->player.where.z - doom->player.eye_lvl;
	dist.z = entity->where.y - doom->player.where.y;
	screen.x = dist.x * doom->player.anglesin - dist.z * doom->player.anglecos;
	screen.z = dist.x * doom->player.anglecos + dist.z * doom->player.anglesin;
	screen.y = dist.y + screen.z * doom->player.pitch;
	screen.x = doom->w2 + (screen.x * doom->cam.scale / -screen.z);
	screen.y = doom->h2 + (screen.y * doom->cam.scale / -screen.z);
	size.x = doom->npc_bxpm[entity->type].pos[entity->state][entity->frame]
	[entity->angle].w * (g_entity_data[entity->type].scale * (doom->surface->w / 100)) / screen.z;
	size.y = doom->npc_bxpm[entity->type].pos[entity->state][entity->frame]
	[entity->angle].h * (g_entity_data[entity->type].scale * (doom->surface->w / 100)) / screen.z;
	render->z = screen.z;
	render->start = new_point(screen.x - size.x / 2, screen.y - size.y);
	render->end = new_point(screen.x + size.x / 2, screen.y);
	render->clamp_start.x = ft_clamp(render->start.x, 0, doom->surface->w - 1);
	render->clamp_end.x = ft_clamp(render->end.x, 0, doom->surface->w - 1);
	render->clamp_start.y = ft_clamp(render->start.y, 0, doom->surface->h - 1);
	render->clamp_end.y = ft_clamp(render->end.y, 0, doom->surface->h - 1);
	render->xrange = render->end.x - render->start.x;
	render->yrange = render->end.y - render->start.y;
}
