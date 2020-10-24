/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:04:51 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/21 18:11:50 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_circle(SDL_Surface *surf, int color, t_ab ab)
{
    ((int*)surf->pixels)[(ab.a1 + ab.a2) * surf->w + (ab.b1 + ab.b2)] = color;
    ((int*)surf->pixels)[(ab.a1 - ab.a2) * surf->w + (ab.b1 + ab.b2)] = color;
    ((int*)surf->pixels)[(ab.a1 + ab.a2) * surf->w + (ab.b1 - ab.b2)] = color;
    ((int*)surf->pixels)[(ab.a1 - ab.a2) * surf->w + (ab.b1 - ab.b2)] = color;
    ((int*)surf->pixels)[(ab.a1 + ab.b2) * surf->w + (ab.b1 + ab.a2)] = color;
    ((int*)surf->pixels)[(ab.a1 - ab.b2) * surf->w + (ab.b1 + ab.a2)] = color;
    ((int*)surf->pixels)[(ab.a1 + ab.b2) * surf->w + (ab.b1 - ab.a2)] = color;
    ((int*)surf->pixels)[(ab.a1 - ab.b2) * surf->w + (ab.b1 - ab.a2)] = color;
}

void				circle(SDL_Surface *surf, Uint32 color, t_xyz xyz)
{
	t_ab ab;
    int dist;

    ab.a1 = xyz.y;
	ab.b1 = xyz.x;
	ab.a2 = 0;
	ab.b2 = xyz.z;
	dist = 3 - 2 * ab.b2;
	draw_circle(surf, color, ab);
	while (ab.b2 >= ab.a2)
	{
		ab.a2++;
		if (dist >= 0)
		{
			ab.b2--;
			dist = dist + 4 * (ab.a2 - ab.b2) + 10;
		}
		else
			dist = dist + 4 * ab.a2 + 6;
		draw_circle(surf, color, ab);
	}
}

void				line(SDL_Surface *surf, int color, t_ab xy)
{
	int			cath_x;
	int			cath_y;
	int			overflow_x;
	int			overflow_y;

	cath_x = (xy.b2 - xy.b1) < 0 ? (xy.b2 - xy.b1) * -1 : (xy.b2 - xy.b1);
	cath_y = (xy.a2 - xy.a1) < 0 ? (xy.a2 - xy.a1) * -1 : (xy.a2 - xy.a1);
	overflow_y = cath_y - cath_x;
	overflow_y = cath_y - cath_x;
	while (xy.a1 != xy.a2 || xy.b1 != xy.b2)
	{
    	((int*)surf->pixels)[xy.b1 * surf->w + xy.a1] = color;
		overflow_x = overflow_y * 2;
		if (overflow_x > -(cath_x))
		{
			overflow_y -= cath_x;
			xy.a1 += xy.a1 < xy.a2 ? 1 : -1;
		}
		else if (overflow_x < cath_x)
		{
			overflow_y += cath_y;
			xy.b1 += xy.b1 < xy.b2 ? 1 : -1;
		}
	}
}

void	map_vertices(t_doom *doom, int color, t_ab ab)
{
	if (ab.a1 >= W || ab.a1 <= 0)
		ab.a1 = ab.a1 >= W ? W - 1 : 0;
	if (ab.b1 >= H || ab.b1 <= 0)
		ab.b1 = ab.b1 >= H ? H - 1 : 0;
	if (ab.a2 >= W || ab.a2 <= 0)
		ab.a2 = ab.a2 >= W ? W - 1 : 0;
	if (ab.b2 >= H || ab.b2 <= 0)
		ab.b2 = ab.b2 >= H ? H - 1 : 0;
	line(doom->surface, color, ab);
}

void DrawMap(t_doom *doom)
{
	t_xyz		a;
	t_xyz		b;
	t_xyz		*vert;
	t_sector	*sect;
	int			color;

	a = (t_xyz){.x = 10, .y = 10};	//size
	b = (t_xyz){.x = (W / 2), .y = (H / 2)}; 	//where
   	line(doom->surface, 0x0000FF, (t_ab){.a1 = b.x, .b1 = b.y,
			.a2 = b.x + PLAYER.anglecos * a.x, .b2 = b.y + PLAYER.anglesin * a.y});
	circle(doom->surface, 0x0000FF, (t_xyz){.x = b.x, .y = b.y, .z = a.x / 2});

	b.x = b.x - PLAYER.where.x * a.x;
	b.y = b.y - PLAYER.where.y * a.y;
	for (unsigned c = 0; c < SECTORNUM; c++)
	{
		sect = &doom->sectors[c];
        vert = sect->vertex;
		if (doom->sectors[PLAYER.sector].floor != sect->floor)
			continue ;
        for (unsigned j = 0; j < sect->npoints; j++)
        {
			color = 0xFFFFFF;
			if (sect->neighbors[j] >= 0 && doom->sectors[sect->neighbors[j]].floor != doom->sectors[PLAYER.sector].floor)
				color = doom->sectors[sect->neighbors[j]].floor > doom->sectors[PLAYER.sector].floor ? 0x00ff00 : 0xff0000;
			else if (sect->neighbors[j] >= 0)
				continue ;
            map_vertices(doom, color, (t_ab){
					.a1 = b.x + vert[j].x * a.x,
					.b1 = b.y + vert[j].y * a.y,
					.a2 = b.x + vert[j + 1].x * a.x,
					.b2 = b.y + vert[j + 1].y * a.y});
        }
	}
}

