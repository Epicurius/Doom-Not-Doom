/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:43:30 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/05 06:45:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Free all allocated entity frame cordinates.
 */
void	free_sprites_pos(t_doom *doom)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < ENTITY_AMOUNT)
	{
		if (doom->eframes[i].pos)
		{
			k = -1;
			while (++k < 4)
			{
				j = -1;
				while (++j < doom->eframes[i].nb[k][FRAMES])
					free(doom->eframes[i].pos[k][j]);
				free(doom->eframes[i].pos[k]);
			}
			free(doom->eframes[i].pos);
		}
	}
}

/*
 *	Free entities.
 */
void	free_entities(t_doom *doom)
{
	t_list	*tmp;
	t_list	*curr;

	curr = doom->entity;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->content);
		free(tmp);
	}
	doom->entity = NULL;
}

/*
 *	Free Rifts.
 */
void	free_rifts(t_doom *doom)
{
	t_list	*tmp;
	t_list	*curr;

	curr = doom->rifts;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->content);
		free(tmp);
	}
	doom->rifts = NULL;
}

/*
 *	Free Textures.
 */
void	free_textures(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < MAP_TEXTURE_AMOUNT)
	{
		free(doom->mtx[i].clr);
		free(doom->mtx[i].pix);
		free_shade_shade(&doom->mtx[i]);
	}
	i = -1;
	while (++i < SKYBOX_TEXTURE_AMOUNT)
	{
		free(doom->stx[i].clr);
		free(doom->stx[i].pix);
	}
	i = -1;
	while (++i < ENTITY_TEXTURE_AMOUNT)
	{
		free(doom->etx[i].clr);
		free(doom->etx[i].pix);
	}
}

/*
 *	Free any remaining projectiles.
 */
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
