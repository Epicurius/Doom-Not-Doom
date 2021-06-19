/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:43:30 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/19 17:43:54 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free_sprites_pos(t_doom *doom)
{
	if (doom->npc_bxpm[0].pos)
		free_sprite_pos(&doom->npc_bxpm[0]);
	if (doom->npc_bxpm[1].pos)
		free_sprite_pos(&doom->npc_bxpm[1]);
	if (doom->npc_bxpm[2].pos)
		free_sprite_pos(&doom->npc_bxpm[2]);
}

void	free_sprites(t_doom *doom)
{
	t_list	*tmp;
	t_list	*curr;

	curr = doom->sprite;
	while (curr)
	{
		free(curr->content);
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}

void	free_rifts(t_doom *doom)
{
	t_list	*tmp;
	t_list	*curr;

	curr = doom->rifts;
	while (curr)
	{
		free(curr->content);
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}

void	free_textures(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		free(doom->mtx[i].clr);
		free(doom->mtx[i].pix);
		free_color_palet(&doom->mtx[i]);
	}
	i = -1;
	while (++i < 12)
	{
		free(doom->stx[i].clr);
		free(doom->stx[i].pix);
	}
	i = -1;
	while (++i < 3)
	{
		free(doom->sprite_sheets[i].clr);
		free(doom->sprite_sheets[i].pix);
	}
}

void	free_projectiles(t_doom *doom)
{
	t_list	*curr;
	t_list	*del;

	curr = doom->orb;
	while (curr)
	{
		del = curr;
		curr = curr->next;
		free(del->content);
		free(del);
	}
}
