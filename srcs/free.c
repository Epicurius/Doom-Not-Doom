/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:11 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/18 09:45:02 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	free_map(t_doom *doom)
{
	int	i;

	ft_memdel((void *)&doom->vert);
	i = -1;
	while (++i < doom->nb.walls)
		ft_memdel((void *)&doom->walls[i].wsprite);
	ft_memdel((void *)&doom->walls);
	i = -1;
	while (++i < doom->nb.sectors)
		ft_memdel((void *)&doom->sectors[i].wall);
	ft_memdel((void *)&doom->sectors);
}

void	free_render_utils(t_doom *doom)
{
	free(doom->zbuffer);
	free(doom->fustrum);
	free(doom->render);
}

void	free_font(t_doom *doom)
{
	TTF_CloseFont(doom->font.amaz50);
	TTF_CloseFont(doom->font.digi100);
}

void	free_color_palet(t_bxpm *bxpm)
{
	int	i;

	i = -1;
	while (++i < 512)
	{
		if (bxpm->palet[i])
			free(bxpm->palet[i]);
	}
}

void	free_sprite_pos(t_npc_bxpm *sprite)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < sprite->nb[i][FRAMES])
			free(sprite->pos[i][j]);
		free(sprite->pos[i]);
	}
	free(sprite->pos);
}

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

void	free_weapons(t_doom *doom)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < (doom->weapon[i].reload_frames
				+ doom->weapon[i].fire_frames))
		{
			free(doom->weapon[i].bxpm[j].pix);
			free(doom->weapon[i].bxpm[j].clr);
		}
		free(doom->weapon[i].bxpm);
	}
}

void	free_sounds(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < 7)
		Mix_FreeChunk(doom->sound[i]);
}

void	free_icon(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		free(doom->icon[i].clr);
		free(doom->icon[i].pix);
	}
}

void	free_doom(t_doom *doom)
{
	free_map(doom);
	free_sprites(doom);
	free_sprites_pos(doom);
	free_rifts(doom);
	free_projectiles(doom);
	free_textures(doom);
	free_icon(doom);
	free_weapons(doom);
	SDL_FreeSurface(doom->time.surf);
	free_render_utils(doom);
	free_font(doom);
	free_sounds(doom);
	free_tpool(&doom->tpool);
	SDL_FreeSurface(doom->surface);
	SDL_DestroyTexture(doom->texture);
	SDL_DestroyTexture(doom->texture);
	SDL_DestroyRenderer(doom->renderer);
	SDL_DestroyWindow(doom->win);
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
	free(doom);
	ft_putstr("All is free!\n");
}
