/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:43:45 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/20 17:09:34 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	 project_game_entity(t_doom *doom, t_entity_render *render)
{
	render->screen.x = doom->w2 + (render->screen.x * doom->cam.scale / -render->screen.z);
	render->screen.y = doom->h2 + (render->screen.y * doom->cam.scale / -render->screen.z);
	render->size.x	= render->pos.w * render->scale / render->screen.z;
	render->size.y	= render->pos.h * render->scale / render->screen.z;
	render->start.x	= render->screen.x - render->size.x / 2;
	render->end.x	= render->screen.x + render->size.x / 2;
	render->start.y = render->screen.y - render->size.y;
	render->end.y	= render->screen.y;
	render->clamp_start.x	= ft_clamp(render->start.x, 0, doom->surface->w - 1);
	render->clamp_end.x	= ft_clamp(render->end.x,   0, doom->surface->w - 1);
	render->clamp_start.y	= ft_clamp(render->start.y, 0, doom->surface->h - 1);
	render->clamp_end.y	= ft_clamp(render->end.y,   0, doom->surface->h - 1);
	render->xrange = render->end.x - render->start.x;
	render->yrange = render->end.y - render->start.y;
}

int	rotate_sprite(t_doom *doom, t_entity *sprite, t_entity_render *render)
{
	t_xyz dist;
	t_xyz screen;

	dist.x = sprite->where.x - doom->player.where.x;
	dist.y = sprite->where.z - doom->player.where.z - EYE_LVL;
	dist.z = sprite->where.y - doom->player.where.y;
	screen.x = dist.x * doom->player.anglesin
			- dist.z * doom->player.anglecos;
	screen.z = dist.x * doom->player.anglecos
			+ dist.z * doom->player.anglesin;
	screen.y = dist.y + screen.z * doom->player.pitch;
	if (screen.z <= 0.3)
		return (0);
	render->screen = xyz(screen.x, screen.y, screen.z);
	render->scale = sprite->data->scale;
	render->pos = doom->sheet[sprite->type].pos[sprite->state][sprite->frame][sprite->angle];
	return (1);
}

void	sprite_threads(t_doom *doom, t_entity_render render, t_entity *sprite, t_entity_render *thread)
{
	int y;

	y = -1;
	int i = render.clamp_end.y - render.clamp_start.y;
	while (++y < 10)
	{
		ft_memcpy((void*)&thread[y], (void*)&render, sizeof(t_entity_render));
		thread[y].clamp_start.y	+= i / 10.0 * y;
		thread[y].clamp_end.y	+= i / 10.0 * (y + 1);
		thread[y].clamp_end.y	= ft_min(thread[y].clamp_end.y, render.clamp_end.y);
		thread[y].surface = doom->surface;
		thread[y].bxpm = &doom->sheet[sprite->type].bxpm;
		thread[y].shooting = doom->player.shooting;
		thread[y].dmg = doom->weapon[doom->player.equiped].damage;
		thread[y].hp = &sprite->hp;
		//thread[y].danger = &sprite->danger;
		tpool_add(&doom->tpool, blit_game_entity, &thread[y]);
	}
}

void	Drawsprite(t_doom *doom)
{
	t_list *curr;
	t_entity *sprite;
	t_entity_render render;
	t_entity_render	thread[10];

	curr = doom->sprite;
	while (curr)
	{
		sprite = curr->content;
		if (doom->sectors[sprite->sector].visible && rotate_sprite(doom, sprite, &render))
		{
			project_game_entity(doom, &render);
			tpool_wait(&doom->tpool);
			sprite_threads(doom, render, sprite, thread);
		}
		curr = curr->next;
	}
	tpool_wait(&doom->tpool);
}
