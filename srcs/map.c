/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:04:51 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/21 14:07:32 by nneronin         ###   ########.fr       */
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

static inline void		clamp_line(SDL_Surface *surf, int x, int y, int color)
{
	int pix;

	pix = (y * surf->w + x);
	if (y < 0 || y > H || x < 0 || x > W)
		return ;
	if (pix > 0 && pix < (surf->w * surf->h))
    		((int*)surf->pixels)[pix] = color;
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
    		clamp_line(surf, xy.a1, xy.b1, color);
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
	//if (ab.a1 >= W || ab.a1 <= 0)
	//	ab.a1 = ab.a1 >= W ? W - 1 : 0;
	//if (ab.b1 >= H || ab.b1 <= 0)
	//	ab.b1 = ab.b1 >= H ? H - 1 : 0;
	//if (ab.a2 >= W || ab.a2 <= 0)
	//	ab.a2 = ab.a2 >= W ? W - 1 : 0;
	//if (ab.b2 >= H || ab.b2 <= 0)
	//	ab.b2 = ab.b2 >= H ? H - 1 : 0;
	line(doom->surface, color, ab);
}

t_xyz	change_line_length(t_doom *doom, float length, float yaw)
{
	t_xyz tmp;
	float dist;
	
	//dist = sqrt(((a.x * a.x) - (b.x * b.x)) + ((a.y * a.y) - (b.y * b.y));
	//tmp.x = b.x - a.x;
	//tmp.y = b.y - a.y;
	//tmp.x = (tmp.x * length) + a.x;
	//tmp.y = (tmp.y * length) + a.y;
	tmp.x = W/2 + cos(yaw) * length;
	tmp.y = H/2 + sin(yaw) * length;
	return (tmp);
}

void	DrawMap(t_doom *doom)
{
	t_xyz		a; //sie of everything
	t_xyz		b; //where on map the player is
	t_wall		*wall;
	t_sector	*sect;
	int		color;

	for (int i = 0; i < W; i++)
	{
		a = (t_xyz){W / 2, H / 2, 0};
		b = (t_xyz){i, 10, 0};
		b = change_line_length(doom, 50, PLAYER.yaw);
		t_ab l = {.a1 = W / 2, .b1 = H / 2, .a2 = b.x, .b2 = b.y};
		
   		line(doom->surface, 0xFF000FF, l);
		
	}


	a = (t_xyz){.x = 5, .y = 5};	//size
	t_ab player_dir		= {.a1 = W / 2, .b1 = H / 2, .a2 = W/2 + PLAYER.anglecos * (a.x * 2),
								.b2 = H/2 + PLAYER.anglesin * (a.y * 2)};
	t_xyz player_circle	= {.x = W / 2, .y = H / 2, .z = a.x};

   	line(doom->surface, 0x0000FF, player_dir);
	circle(doom->surface, 0x0000FF, player_circle);

	b.x = W/2 - PLAYER.where.x * a.x;
	b.y = H/2 - PLAYER.where.y * a.y;




	for (unsigned c = 0; c < SECTORNUM; c++)
	{
		sect = &doom->sectors[c];
        	wall = sect->wall;
		if (doom->sectors[PLAYER.sector].floor != sect->floor)
			continue ;
        	for (unsigned j = 0; j < sect->npoints; j++)
        	{
			color = 0xFFFFFF;
			if (wall[j].n >= 0 && doom->sectors[wall[j].n].floor != doom->sectors[PLAYER.sector].floor)
				color = doom->sectors[wall[j].n].floor > doom->sectors[PLAYER.sector].floor ? 0x00ff00 : 0xff0000;
			else if (sect->wall[j].n >= 0)
				continue ;
			map_vertices(doom, color, (t_ab){
					.a1 = b.x + wall[j].v1.x * a.x,
					.b1 = b.y + wall[j].v1.y * a.y,
					.a2 = b.x + wall[j].v2.x * a.x,
					.b2 = b.y + wall[j].v2.y * a.y});
		}
	}
}
