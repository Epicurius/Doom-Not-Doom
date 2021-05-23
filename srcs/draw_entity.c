/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:43:45 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/23 18:00:35 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	sprite_threads(t_doom *doom, t_entity *sprite, t_entity_thread *thread)
{
	int y;
	int i;
	int t = 5;

	y = -1;
	i = (sprite->render.clamp_end.y - sprite->render.clamp_start.y) / t;
	while (++y < t)
	{
		thread[y].render = sprite->render;
		thread[y].render.clamp_start.y += i * y;
		thread[y].render.clamp_end.y = thread[y].render.clamp_start.y + i;
		if (y == t - 1)
			thread[y].render.clamp_end.y = sprite->render.clamp_end.y;
		thread[y].surface = doom->surface;
		thread[y].bxpm = &doom->sheet[sprite->type].bxpm;
		thread[y].pos = doom->sheet[sprite->type].pos[sprite->state][sprite->frame][sprite->angle];
		thread[y].shooting = doom->player.shooting;
		thread[y].dmg = doom->weapon[doom->player.equiped].damage;
		thread[y].hp = &sprite->hp;
		thread[y].center = doom->c;
		tpool_add(&doom->tpool, blit_game_entity, &thread[y]);
	}

}

void	Drawsprite(t_doom *doom)
{
	t_list *curr;
	t_entity *sprite;
	t_entity_thread	thread[5];

	curr = doom->sprite;
	while (curr != NULL)
	{
		sprite = curr->content;
		if (doom->sectors[sprite->sector].visible && sprite->render.z > 0.3)
		{
			tpool_wait(&doom->tpool);
			sprite_threads(doom, sprite, thread);
		}
		curr = curr->next;
	}
	tpool_wait(&doom->tpool);
}
