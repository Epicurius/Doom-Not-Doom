/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_projectile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:44:04 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/30 11:45:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	project_projectile(t_doom *doom, t_projectile *orb,
	t_entity_thread thread, t_entity_render *render)
{
	t_point	size;
	t_v3	dist;
	t_v3	screen;

	dist.x = orb->where.x - doom->player.where.x;
	dist.y = orb->where.z - doom->player.where.z - doom->player.eyelvl;
	dist.z = orb->where.y - doom->player.where.y;
	screen.x = dist.x * doom->player.anglesin - dist.z * doom->player.anglecos;
	screen.z = dist.x * doom->player.anglecos + dist.z * doom->player.anglesin;
	screen.y = dist.y + screen.z * doom->player.pitch + (4.5);
	screen.x = doom->c.x + (screen.x * doom->cam.scale / -screen.z);
	screen.y = doom->c.y + (screen.y * doom->cam.scale / -screen.z);
	size.x = thread.pos.w * 35 / screen.z;
	size.y = thread.pos.h * 35 / screen.z;
	render->z = screen.z;
	render->start.x = screen.x - size.x / 2;
	render->end.x = screen.x + size.x / 2;
	render->start.y = screen.y - size.y;
	render->end.y = screen.y;
	render->clamp_start.x = ft_clamp(render->start.x, 0, doom->surface->w - 1);
	render->clamp_end.x = ft_clamp(render->end.x, 0, doom->surface->w - 1);
	render->clamp_start.y = ft_clamp(render->start.y, 0, doom->surface->h - 1);
	render->clamp_end.y = ft_clamp(render->end.y, 0, doom->surface->h - 1);
	render->xrange = render->end.x - render->start.x;
	render->yrange = render->end.y - render->start.y;
}

void	draw_projectiles(t_doom *doom)
{
	t_list			*curr;
	t_projectile	*orb;
	t_entity_thread	thread;

	thread.hp = NULL;
	thread.bxpm = &doom->etx[1];
	thread.pos = rect_xy2(810, 76, 856, 119);
	thread.surface = doom->surface;
	curr = doom->orb;
	while (curr)
	{
		orb = curr->content;
		if (doom->sectors[orb->sector].visible)
		{
			project_projectile(doom, orb, thread, &thread.render);
			if (thread.render.z > 0.5)
				blit_game_entity(&thread);
		}
		curr = curr->next;
	}
}
