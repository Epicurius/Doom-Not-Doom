/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:47 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/19 13:49:27 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	scale_wall_height(t_doom *doom, t_wall *wall)
{
	wall->height = doom->sectors[wall->sect].ceiling.height
		- doom->sectors[wall->sect].floor.height;
	wall->text_pix_nb.y = (doom->mtx[wall->wtx].h / wall->scale_factor)
		* wall->height;
}

static void	init_wsprite_scale(t_doom *doom, t_wall *wall)
{
	int			i;
	t_v2		p;
	t_wsprite	*wsprite;

	i = -1;
	while (++i < wall->wsprite.total)
	{
		wsprite = &wall->wsprite.num[i];
		p.x = doom->mtx[wsprite->tx].w;
		p.y = doom->mtx[wsprite->tx].h;
		if (wsprite->state != 0)
			p = new_v2(64, 64);
		if (wsprite->tx == 28)
			p = new_v2(662, 550);
		wsprite->scale_h = p.y / p.x * wsprite->scale_w;
		wsprite->scale_w = p.x / wsprite->scale_w * wall->width;
		wsprite->scale_h = p.y / wsprite->scale_h * wall->height;
		wsprite->src = rect_xy2(0, 0, p.x, p.y);
	}
}

void	init_scale(t_doom *doom)
{
	int		i;
	t_wall	*wall;

	i = -1;
	while (++i < doom->nb.walls)
	{
		wall = &doom->walls[i];
		wall->width = point_distance_v2(wall->v1.x, wall->v1.y,
				wall->v2.x, wall->v2.y);
		wall->height = doom->sectors[wall->sect].ceiling.height
			- doom->sectors[wall->sect].floor.height;
		wall->text_pix_nb.x = (doom->mtx[wall->wtx].w / wall->scale_factor)
			* wall->width;
		wall->text_pix_nb.y = (doom->mtx[wall->wtx].h / wall->scale_factor)
			* wall->height;
		init_wsprite_scale(doom, wall);
	}
}
