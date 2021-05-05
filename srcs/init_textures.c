/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/05 10:58:09 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_entity_pos(t_doom *doom)
{
	init_alfred(&doom->sheet[0]);
	init_spooky(&doom->sheet[1]);
	init_rift(&doom->sheet[2]);
}

void	init_textures(t_doom *doom)
{
	init_clock(doom);
	load_bbmp(doom);
	init_entity_pos(doom);
	color_palets(doom);
}
