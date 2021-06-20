/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 11:00:22 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/20 11:01:17 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_minimap(t_doom *doom)
{
	int		h;
	t_map	*map;

	map = &doom->map;
	h = doom->surface->h * (float)MM_SCALE;
	map->size = rect_xy2(doom->w2 - h / 2, doom->h2 - h / 2,
			doom->w2 + h / 2, doom->h2 + h / 2);
	map->pos_x = doom->w2;
	map->pos_y = doom->h2;
}
