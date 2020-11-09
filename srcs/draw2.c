/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:09:28 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/09 20:05:28 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
/*
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

void	horz_surf_to_vert(t_render *render, float mapY, int screenX, int screenY, t_xyz *map)
{
	map->z = mapY * VERT_FOV / (( H / 2 - screenY) - render->player.yaw * VERT_FOV);
	map->x = map->z * (W / 2 - screenX) / HORI_FOV;
	float rtx = map->z * render->player.anglecos + map->x * render->player.anglesin;
	float rtz = map->z * render->player.anglesin - map->x * render->player.anglecos;
	map->x = rtx + render->player.where.x;
	map->z = rtz + render->player.where.y;
}

int			floor_and_ceiling_texture(void	*arg)
{
	t_render *render = arg;
	int tx;
	int ty;
	t_xyz map;

	for (int y = render->ytop; y <= render->ybottom; ++y)
	{
		if (y >= render->cy.a1 && y <= render->cy.b1)
		{
			y = render->cy.b1;
			continue;
		}
		float hei = y < render->cy.a1 ? render->yceil : render->yfloor;
		horz_surf_to_vert(render, hei, render->x, y, &map);
		tx = (map.x * (64 / 4));
		ty = (map.z * (64 / 4));

		//((int*)doom->surface->pixels)[y * doom->surface->w + x] =
		//	shade_hex_color(((int*)texture->pixels)[(ty % 64) * 64 + (tx % 64)], 0.5);
		((int*)render->surface->pixels)[y * W + render->x] = ((int*)render->txtx->pixels)[(ty % 64) * 64 + (tx % 64)];
	}
	return (0);
}*/

void		DrawScreen(t_doom *doom)
{
	char		rendered[SECTORNUM];
	t_item		queue[MAXQUEUE];
	t_item		*head = queue;
	t_item		*tail = queue;
	t_item		curr;

	bzero(rendered, (sizeof(char*) * SECTORNUM));
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
		if (rendered[curr.sectorno] > 1)
			continue ;
		draw_sector(doom, queue, &head, tail, curr);
		rendered[curr.sectorno] += 1;
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
	t_render	render[W];
   	sect = &doom->sectors[curr.sectorno];
	while (++s < sect->npoints)
	{
		rotate_wall_sector(sect, s, &doom->player, SECTORS->viewed_sectors);
		if (SECTORS->viewed_sectors[0].z <= 0 && SECTORS->viewed_sectors[1].z <= 0)
			continue;
		doom->u0 = 0; //start_x of text
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
		render_wall(doom, curr, sect->neighbors[s], render);
		if (sect->neighbors[s] >= 0 && doom->end_x >= doom->start_x && (*head + MAXQUEUE + 1 - tail) % MAXQUEUE)
		{
			*(*head) = (t_item){.sectorno = sect->neighbors[s], .sx1 = doom->start_x, .sx2 = doom->end_x};
			if (++(*head) == queue + MAXQUEUE)
				(*head) = queue;
		}
	}
	tpool_wait(&doom->tpool);
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

void			draw_portal(t_render *render, t_ab y, t_ab cy)
{
	if (render->texture)
	{
		vline1(render, cy.b2, cy.b1, G); //-1
		vline1(render, cy.a1, cy.a2, G); //+1
	}
	else
	{
		t_vline3(render,	(t_ab){.a1 = y.a1,		.b1 = y.b1},
							(t_ab){.a1 = cy.a1, 	.b1 = y.a2});
		t_vline3(render,	(t_ab){.a1 = y.a1,		.b1 = y.b1},
							(t_ab){.a1 = cy.b2,		.b1 = cy.b1});
	}
	render->ytop[render->x] = clamp(max(cy.a1, cy.a2), render->ytop[render->x], H - 1);
	render->ybottom[render->x] = clamp(min(cy.b1, cy.b2), 0, render->ybottom[render->x]);
}

static inline int	kortare(t_render *render, int a, int b)
{
	//int i = (render->x - render->x1);
	//int j = i * (b - a);
   	int y = (render->x2 - render->x1);
	if (y == 0)
		return (a);
	else
		return ((((render->x - render->x1) * (b - a)) / y) + a);
}

static inline void	affine_tranformation_of_texture(t_doom *doom, int x, int *affine_x)
{
	float a = (SECTORS->viewpoint.x2 - x) * SECTORS->viewed_sectors[1].z;
	float b = (x - SECTORS->viewpoint.x1) * SECTORS->viewed_sectors[0].z;
	*affine_x = (int)((doom->u0 * a + doom->u1 * b) / (a + b));
}

void		init_thread(t_render *render, int x, t_doom *doom, int neighbor)
{
	render->x = x;
	render->surface = doom->surface;
	render->txtx = doom->txtx;
	render->neighbor = neighbor;
	render->texture = doom->key.t;
	render->ytop = doom->ytop;
	render->ybottom = doom->ybottom;
	render->img_res = IMG_RES;
	affine_tranformation_of_texture(doom, x, &render->affine_x);
	render->player = doom->player;
	render->height_info = doom->height_info;
	render->x1 = doom->sectors->viewpoint.x1;
	render->x2 = doom->sectors->viewpoint.x2;
}

int				thread_render(void *arg)
{
	t_ab		y;		//un clmaped
	t_ab		cy;		//clamped
	t_render	*render;

	render = arg;
   	y.a1 = kortare(render, render->height_info.y.a1, render->height_info.y.a2);
   	y.b1 = kortare(render, render->height_info.y.b1, render->height_info.y.b2);
	cy.a1 = clamp(y.a1, render->ytop[render->x], render->ybottom[render->x]);
	cy.b1 = clamp(y.b1, render->ytop[render->x], render->ybottom[render->x]);

	vline1(render, render->ytop[render->x], cy.a1 - 1, G);		//ceil
	vline1(render, cy.b1 + 1, render->ybottom[render->x], 0xb47044);	//floor
	
	//tpool_add(&doom->tpool, floor_and_ceiling_texture, &render[x]);
	if (render->neighbor >= 0)
	{
   		y.a2 = kortare(render, render->height_info.ny.a1, render->height_info.ny.a2);
   		y.b2 = kortare(render, render->height_info.ny.b1, render->height_info.ny.b2);
		cy.a2 = clamp(y.a2, render->ytop[render->x], render->ybottom[render->x]);
		cy.b2 = clamp(y.b2, render->ytop[render->x], render->ybottom[render->x]);
		draw_portal(render, y, cy);
	}
	if (render->texture)
		vline1(render, cy.a1, cy.b1, 0x959392);
	else
		t_vline3(render, y, cy);
	return (0);
}

void		render_wall(t_doom *doom, t_item curr, int neighbor, t_render *render)
{
	int		x;

   	doom->start_x	= max(SECTORS->viewpoint.x1, curr.sx1);		//screen fist wall pixel
	doom->end_x		= min(SECTORS->viewpoint.x2, curr.sx2);		//screen last wall pixel
	x = doom->start_x;
	while (x < doom->end_x) //<=
	{
		init_thread(&render[x], x, doom, neighbor);
   		render[x].light = doom->sectors[curr.sectorno].light;
		tpool_add(&doom->tpool, thread_render, &render[x]);	
		x += 1;
	}
}
