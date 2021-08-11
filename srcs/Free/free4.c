/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:44:12 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/11 12:46:13 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Free weapons.
 */
void	free_weapons(t_doom *doom)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WEAPON_AMOUNT)
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

/*
 *	Free all sounds.
 */
void	free_sounds(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < WAV_AMOUNT)
		Mix_FreeChunk(doom->sound[i]);
}

/*
 *	Free all icons aka HUD.
 */
void	free_icon(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < ICON_TEXTURE_AMOUNT)
	{
		free(doom->itx[i].clr);
		free(doom->itx[i].pix);
	}
}
