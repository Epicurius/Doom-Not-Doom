/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:43:01 by nneronin          #+#    #+#             */
/*   Updated: 2021/11/23 09:31:37 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Free the map.
 */
void	free_map(t_doom *doom)
{
	int	i;

	
	i = -1;
	while (++i < doom->nb.walls)
		ft_memdel((void *)&doom->walls[i].wsprite);
	ft_memdel((void *)&doom->walls);
	i = -1;
	while (++i < doom->nb.sectors)
		ft_memdel((void *)&doom->sectors[i].wall);
	ft_memdel((void *)&doom->sectors);
	i = -1;
	while (++i < doom->nb.events)
		if (doom->events[i].audio)
			Mix_FreeChunk(doom->events[i].audio);
	ft_memdel((void *)&doom->events);
}

/*
 *	Free non SDL render utils
 */
void	free_render_utils(t_doom *doom)
{
	free(doom->zbuffer);
	free(doom->render);
	free(doom->sectbool);
}

/*
 *	Free all TTF_Fonts.
 */
void	free_font(t_doom *doom)
{
	TTF_CloseFont(doom->font.amaz);
	TTF_CloseFont(doom->font.digital);
}

/*
 *	Free all BXPM shade shades.
 */
void	free_shade_shade(t_bxpm *bxpm)
{
	int	i;

	i = -1;
	while (++i < 512)
	{
		if (bxpm->shade[i])
			free(bxpm->shade[i]);
	}
}
