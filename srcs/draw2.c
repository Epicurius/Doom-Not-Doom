/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:09:28 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/02 17:41:06 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	horz_surf_to_vert(t_doom *doom, float mapY, int screenX, int screenY, t_xyz *map)
{
	map->z = mapY * VERT_FOV / (( H / 2 - screenY) - PLAYER.yaw * VERT_FOV);
	map->x = map->z * (W / 2 - screenX) / HORI_FOV;
	float rtx = map->z * PLAYER.anglecos + map->x * PLAYER.anglesin;
	float rtz = map->z * PLAYER.anglesin - map->x * PLAYER.anglecos;
	map->x = rtx + PLAYER.where.x;
	map->z = rtz + PLAYER.where.y;
}

void				floor_and_ceiling_texture(t_doom *doom, int x, t_ab y, t_ab cy)
{
	int tx;
	int ty;
	t_xyz map;
	SDL_Surface *texture;

	for (int y = doom->ytop[x]; y <= doom->ybottom[x]; ++y)
	{
		if (y >= cy.a1 && y <= cy.b1)
		{
			y = cy.b1;
			continue;
		}
		float hei = y < cy.a1 ? HEIGHT_INFO.yceil : HEIGHT_INFO.yfloor;
		horz_surf_to_vert(doom, hei, x, y, &map);
		tx = (map.x * (64 / 4));
		ty = (map.z * (64 / 4));

		texture = y < cy.a1 ? doom->txtx1 : doom->txtx1;
		//((int*)doom->surface->pixels)[y * doom->surface->w + x] =
		//	shade_hex_color(((int*)texture->pixels)[(ty % 64) * 64 + (tx % 64)], 0.5);
		((int*)doom->surface->pixels)[y * doom->surface->w + x] = ((int*)texture->pixels)[(ty % 64) * 64 + (tx % 64)];
	}
}

void		DrawScreen(t_doom *doom)
{
	int			renderedsectors[SECTORNUM];
	t_item		queue[MAXQUEUE];
	t_item		*head = queue;
	t_item		*tail = queue;
	t_item		curr;

	//bzero(renderedsectors, (sizeof(int*) * SECTORNUM));
	//bzero(doom->ytop, (sizeof(int*) * W));
    for (unsigned x = 0; x < SECTORNUM; ++x)
		renderedsectors[x] = 0;
    for (unsigned x = 0; x < W; ++x)
	{
		doom->ytop[x] = 0;
		doom->ybottom[x] = H - 1;
	}

	*head = (t_item){.sectorno = PLAYER.sector, .sx1 = 0, .sx2 = W - 1};
    if (++head == queue + MAXQUEUE) //iterate head and check if queue is max
		head = queue;
	while (head != tail) // render any other queued sectors
	{
    	curr = *tail;
    	if (++tail == queue + MAXQUEUE)
			tail = queue;
		if (renderedsectors[curr.sectorno] & 0x21)
			continue ;
		++renderedsectors[curr.sectorno];
		draw_sector(doom, queue, &head, tail, curr);
		//SDL_UpdateWindowSurface(doom->win);
		//SDL_Delay(1000);
		++renderedsectors[curr.sectorno];
	}
}

/*
** Render each wall of this sector that is facing towards PLAYER.
*/
void		draw_sector(t_doom *doom, t_item *queue, t_item **head, t_item *tail, t_item curr)
{
	int			s;
	t_sector	*sect;

	s = -1;
   	sect = &doom->sectors[curr.sectorno];
	doom->light = sect->light;
	while (++s < sect->npoints)
	{
		rotate_wall_sector(sect, s, &doom->player, SECTORS->viewed_sectors);
		if (SECTORS->viewed_sectors[0].z <= 0 && SECTORS->viewed_sectors[1].z <= 0)
			continue;
		doom->u0 = 0; //start_x of text
		//doom->u1 = IMG_RES; //end_x of text (technecally wall width)
		doom->u1 = ft_pythagoras(	fabs(sect->vertex[s].x - sect->vertex[s + 1].x),
									fabs(sect->vertex[s].y - sect->vertex[s + 1].y));
		doom->u1 *= (IMG_RES / 6.4);// / 2;
		if (SECTORS->viewed_sectors[0].z <= 0 || SECTORS->viewed_sectors[1].z <= 0)
			player_view_fustrum(doom, SECTORS->viewed_sectors);
		player_perspective_tranformation(&SECTORS->viewpoint, SECTORS->viewed_sectors);
		if (SECTORS->viewpoint.x1 >= SECTORS->viewpoint.x2 ||
				SECTORS->viewpoint.x2 < curr.sx1 ||
				SECTORS->viewpoint.x1 > curr.sx2) // Only render if it's visible
			continue;
		floor_ceiling_heights(doom, sect->neighbors[s], sect);
		render_wall(doom, curr, sect->neighbors[s]);
		if (sect->neighbors[s] >= 0 && doom->end_x >= doom->start_x && (*head + MAXQUEUE + 1 - tail) % MAXQUEUE)
		{
			*(*head) = (t_item){.sectorno = sect->neighbors[s], .sx1 = doom->start_x, .sx2 = doom->end_x};
			if (++(*head) == queue + MAXQUEUE)
				(*head) = queue;
		}
		//SDL_UpdateWindowSurface(doom->win);
		//SDL_Delay(1000);
	}
}

void		floor_ceiling_heights(t_doom *doom, int neighbor, t_sector *sect)
{
	HEIGHT_INFO.nyceil	= 0;
	HEIGHT_INFO.nyfloor	= 0;
	HEIGHT_INFO.yceil	= sect->ceil - PLAYER.where.z;
	HEIGHT_INFO.yfloor	= sect->floor - PLAYER.where.z;
   	if (neighbor >= 0)
  	{
		HEIGHT_INFO.nyceil  = doom->sectors[neighbor].ceil  - PLAYER.where.z;
		HEIGHT_INFO.nyfloor = doom->sectors[neighbor].floor - PLAYER.where.z;
   	}
   	HEIGHT_INFO.y.a1 =	H / 2 - (int)(Yaw(HEIGHT_INFO.yceil, SECTORS->viewed_sectors[0].z) * SECTORS->viewpoint.yscale1);
	HEIGHT_INFO.y.b1 =	H / 2 - (int)(Yaw(HEIGHT_INFO.yfloor, SECTORS->viewed_sectors[0].z) * SECTORS->viewpoint.yscale1);
   	HEIGHT_INFO.y.a2 =	H / 2 - (int)(Yaw(HEIGHT_INFO.yceil, SECTORS->viewed_sectors[1].z) * SECTORS->viewpoint.yscale2);
	HEIGHT_INFO.y.b2 =	H / 2 - (int)(Yaw(HEIGHT_INFO.yfloor, SECTORS->viewed_sectors[1].z) * SECTORS->viewpoint.yscale2);
   	HEIGHT_INFO.ny.a1 = H / 2 - (int)(Yaw(HEIGHT_INFO.nyceil, SECTORS->viewed_sectors[0].z) * SECTORS->viewpoint.yscale1);
	HEIGHT_INFO.ny.b1 = H / 2 - (int)(Yaw(HEIGHT_INFO.nyfloor, SECTORS->viewed_sectors[0].z) * SECTORS->viewpoint.yscale1);
   	HEIGHT_INFO.ny.a2 = H / 2 - (int)(Yaw(HEIGHT_INFO.nyceil, SECTORS->viewed_sectors[1].z) * SECTORS->viewpoint.yscale2);
	HEIGHT_INFO.ny.b2 = H / 2 - (int)(Yaw(HEIGHT_INFO.nyfloor, SECTORS->viewed_sectors[1].z) * SECTORS->viewpoint.yscale2);
}

void				floor_and_ceiling_color(t_doom *doom, int x, t_ab y, t_ab cy)
{
	vline(doom, x, doom->ytop[x], cy.a1 - 1);		//ceil
	vline(doom, x, cy.b1 + 1, doom->ybottom[x]);	//floor
}

void			draw_portal(t_doom *doom, int x, t_ab y, t_ab cy)
{
	if (doom->key.t)
	{
		vline(doom, x, cy.b2 + 1, cy.b1);
		vline(doom, x, cy.a1, cy.a2 - 1);
	}
	else
	{
		t_vline1(doom, x,	(t_ab){.a1 = y.a1,		.b1 = y.b1},
							(t_ab){.a1 = cy.a1, 	.b1 = y.a2 - 1}, doom->light);
		t_vline1(doom, x,	(t_ab){.a1 = y.a1,		.b1 = y.b1},
							(t_ab){.a1 = cy.b2 + 1,	.b1 = cy.b1}, doom->light);
	}
	doom->ytop[x] = clamp(max(cy.a1, cy.a2), doom->ytop[x], H - 1);
	doom->ybottom[x] = clamp(min(cy.b1, cy.b2), 0, doom->ybottom[x]);
}

static inline int	y_cordinate_for_floor_and_ceiling(t_doom *doom, int x, int a, int b)
{
	int y;

   	y = (x - SECTORS->viewpoint.x1) * (b - a) / (SECTORS->viewpoint.x2 - SECTORS->viewpoint.x1) + a;
	//y = clamp(y, SECTORS->ytop[x], SECTORS->ybottom[x]);
	return (y);
}

static inline void	affine_tranformation_of_texture(t_doom *doom, int x)
{
	float a = (SECTORS->viewpoint.x2 - x) * SECTORS->viewed_sectors[1].z;
	float b = (x - SECTORS->viewpoint.x1) * SECTORS->viewed_sectors[0].z;
	doom->affine_x = (doom->u0 * a + doom->u1 * b) / (a + b);
}

void		render_wall(t_doom *doom, t_item curr, int neighbor)
{
	int		x;
	t_ab	y;	//un clmaped
	t_ab	cy;	//clamped

   	doom->start_x	= max(SECTORS->viewpoint.x1, curr.sx1);	//screen fist wall pixel
	doom->end_x		= min(SECTORS->viewpoint.x2, curr.sx2);		//screen last wall pixel
	x = doom->start_x;
	while (x <= doom->end_x)
	{
		affine_tranformation_of_texture(doom, x);
    	y.a1 = y_cordinate_for_floor_and_ceiling(doom, x, HEIGHT_INFO.y.a1, HEIGHT_INFO.y.a2);
    	y.b1 = y_cordinate_for_floor_and_ceiling(doom, x, HEIGHT_INFO.y.b1, HEIGHT_INFO.y.b2);
		cy.a1 = clamp(y.a1, doom->ytop[x], doom->ybottom[x]); //move the 2 to neighbour
		cy.b1 = clamp(y.b1, doom->ytop[x], doom->ybottom[x]);
		if (1 || doom->key.t)
			floor_and_ceiling_color(doom, x, y, cy);
		else
			floor_and_ceiling_texture(doom, x, y, cy);
			//floor_text(doom, x, cy.b1 + 1, doom->ybottom[x]);	//floor

		if (neighbor >= 0)
		{
    		y.a2 = y_cordinate_for_floor_and_ceiling(doom, x, HEIGHT_INFO.ny.a1, HEIGHT_INFO.ny.a2);
    		y.b2 = y_cordinate_for_floor_and_ceiling(doom, x, HEIGHT_INFO.ny.b1, HEIGHT_INFO.ny.b2);
			cy.a2 = clamp(y.a2, doom->ytop[x], doom->ybottom[x]);
			cy.b2 = clamp(y.b2, doom->ytop[x], doom->ybottom[x]);
			draw_portal(doom, x, y, cy);
		}
		else if (doom->key.t)
			vline(doom, x, cy.a1, cy.b1);
		else
			t_vline1(doom, x, y, cy, doom->light);
		x += 1;
		//SDL_UpdateWindowSurface(doom->win);
		//SDL_Delay(5);
	}
}
