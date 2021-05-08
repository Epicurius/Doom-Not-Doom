/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_projectile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:44:04 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/08 13:49:00 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	 project_game(t_doom *doom, t_entity_render *render)
{
	render->screen.x = doom->w2 + (render->screen.x * doom->cam.scale / -render->screen.z);
	render->screen.y = doom->h2 + (render->screen.y * doom->cam.scale / -render->screen.z);
	render->size.x	= render->pos.w * 35 / render->screen.z;
	render->size.y	= render->pos.h * 35 / render->screen.z;
	render->start.x	= render->screen.x - render->size.x / 2;
	render->end.x	= render->screen.x + render->size.x / 2;
	render->start.y = render->screen.y - render->size.y;
	render->end.y	= render->screen.y;
	render->clamp_start.x	= ft_clamp(render->start.x, 0, doom->surface->w - 1);
	render->clamp_end.x		= ft_clamp(render->end.x,   0, doom->surface->w - 1);
	render->clamp_start.y	= ft_clamp(render->start.y, 0, doom->surface->h - 1);
	render->clamp_end.y		= ft_clamp(render->end.y,   0, doom->surface->h - 1);
	render->xrange = render->end.x - render->start.x;
	render->yrange = render->end.y - render->start.y;
}

void	rotate_projectile(t_doom *doom, t_project *orb, t_entity_render *render)
{
	t_xyz dist;
	t_xyz screen;

	dist.x 		= orb->where.x - doom->player.where.x;
	dist.y 		= orb->where.z - doom->player.where.z - EYE_LVL;
	dist.z		= orb->where.y - doom->player.where.y;
	screen.x 	= dist.x * doom->player.anglesin - dist.z * doom->player.anglecos;
	screen.z 	= dist.x * doom->player.anglecos + dist.z * doom->player.anglesin;
	screen.y 	= dist.y + screen.z * doom->player.pitch + (4.5);
	render->screen	= xyz(screen.x, screen.y, screen.z);
}

void 	DrawProjectiles(t_doom *doom)
{
	t_list *curr;
	t_project *orb;
	t_entity_render render;

	render.hp		= NULL;
	render.bxpm		= &doom->sheet[1].bxpm;
	render.pos		= new_rect(810, 76, 856, 119);
	render.surface	= doom->surface;
	curr = doom->orb;
	while (curr)
	{
		orb = curr->content;
		if (doom->sectors[orb->sector].visible)
		{
			rotate_projectile(doom, orb, &render);
			if (render.screen.z > 0.5)
			{
				project_game(doom, &render);
				blit_game_entity(&render);
			}
		}
		curr = curr->next;
	}
}
