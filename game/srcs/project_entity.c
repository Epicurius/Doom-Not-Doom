/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

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
	size.x = doom->eframes[e->type].pos[e->state][e->frame][e->angle].w
		/ g_entity_data[e->type].scale * doom->cam.scale / screen.z;
	size.y = doom->eframes[e->type].pos[e->state][e->frame][e->angle].h
		/ g_entity_data[e->type].scale * doom->cam.scale / screen.z;
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
