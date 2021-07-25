/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 11:00:22 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/25 10:35:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_minimap(t_doom *doom)
{
	int		h;
	t_map	*map;

	map = &doom->map;
	h = doom->surface->h * (float)MM_SCALE;
	map->size = rect_xy2(doom->c.x - h / 2, doom->c.y - h / 2,
			doom->c.x + h / 2, doom->c.y + h / 2);
	map->pos.x = doom->c.x;
	map->pos.y = doom->c.y;
}
