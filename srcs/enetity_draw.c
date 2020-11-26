/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enetety_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:47:53 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/26 14:08:11 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

float		dist_calc(float x1, float y1, float x2, float y2)
{
	return (((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

void		z_order(t_player p, t_entity *e, short e_nb)
{
	int			i;
	t_entity	tmp;

	i = -1;
	while (++i < e_nb)
		e[i].dist = dist_calc(e[i].where.x, e[i].where.y, p.where.x, p.where.y);
	i = 0;
	while (i < e_nb - 1)
	{
		if (e[i].dist < e[i + 1].dist)
		{
			tmp = e[i];
			e[i] = e[i + 1];
			e[i + 1] = tmp;
			i = 0;
		}
		i += 1;
	}
}

void		render_entity(t_doom *doom, t_sector *sect, int sect_num)
{
	int			i;
	t_xyz		v2;
	t_entity	e[10]; //change if more 

	int a = 0;
	for (int i = 0; i < ENTITYNUM; i++)
	{
		if (doom->entity[i].sect == sect_num)
			e[a++] = doom->entity[i];
	}
	if (a == 0)
		return ;
	z_order(doom->player, e, a);
	i = -1;
	while (++i < a)
	{
		v2.x = 	(e[i].where.x - PLAYER.where.x) * PLAYER.anglesin -
				(e[i].where.y - PLAYER.where.y) * PLAYER.anglecos;
		v2.y = 	(e[i].where.x - PLAYER.where.x) * PLAYER.anglecos +
				(e[i].where.y - PLAYER.where.y) * PLAYER.anglesin;
		if (v2.y <= 0)
			continue ;
  		//int a =	H / 2 - (int)(Yaw(30 - PLAYER.where.z,	v2.y) *
			//(float)(VERT_FOV / v2.y));
		int b =	H / 2 - (int)(Yaw(0 - PLAYER.where.z,	v2.y) * (float)(VERT_FOV / v2.y));
		int w = doom->imp->w * ((float)(VERT_FOV / v2.y) / 100);
		int h = doom->imp->h * ((float)(VERT_FOV / v2.y) / 100);
		int x = W / 2 - (int)(v2.x * (float)(HORI_FOV / v2.y)) - (w / 2);
		int y = b - h;
		SDL_Rect r = {.x = x, .y = y, .w = w, .h = h};
		SDL_BlitScaled(doom->imp, NULL, doom->surface, &r);
	}
}
