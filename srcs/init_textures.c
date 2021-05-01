/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:05:32 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/01 17:43:14 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_textures(t_doom *doom)
{
	doom->time.clock_font = TTF_OpenFont("./resources/font/digital.ttf", 100);
	init_clock(doom);
	//load_bxpm(doom);
	load_bbmp(doom);
	init_alfred(&doom->sheet[0]);
	init_spooky(&doom->sheet[1]);
	init_spooky(&doom->sheet[2]);
	color_palets(doom);
}
