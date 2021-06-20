/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:43:01 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/20 11:41:12 by nneronin         ###   ########.fr       */
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
	free(doom->render);
}

void	free_font(t_doom *doom)
{
	TTF_CloseFont(doom->font.amaz50);
	TTF_CloseFont(doom->font.digi50);
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
