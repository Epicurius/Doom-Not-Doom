/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:09:28 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/15 18:23:54 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void drawCircle(SDL_Surface *surf, int xc, int yc, int x, int y) 
{ 
	int c = 0xFFFFFFFF;
	((int*)surf->pixels)[(xc+x) + W * (yc+y)] = c;
	((int*)surf->pixels)[(xc-x) + W * (yc+y)] = c;
	((int*)surf->pixels)[(xc+x) + W * (yc-y)] = c;
	((int*)surf->pixels)[(xc-x) + W * (yc-y)] = c;
	((int*)surf->pixels)[(xc+y) + W * (yc+x)] = c;
	((int*)surf->pixels)[(xc-y) + W * (yc+x)] = c;
	((int*)surf->pixels)[(xc+y) + W * (yc-x)] = c;
	((int*)surf->pixels)[(xc-y) + W * (yc-x)] = c;
}

void				ft_circle(SDL_Surface *surf, int xc, int yc, int r)
{
	int x;
	int y;
    int dist;

    x = 0;
	y = r;
	dist = 3 - 2 * r;
	while (y >= x)
	{
		x++;
		if (dist >= 0)
		{
			y--;
			dist = dist + 4 * (x - y) + 10;
		}
		else
			dist = dist + 4 * x + 6;
		drawCircle(surf, xc, yc, x, y);
	}
}

static inline void	horz_surf_to_vert(t_render *render, float mapY, int screenX, int screenY, t_xyz *map)
{
	t_player player;

	player = render->player;
	map->y = mapY * VERT_FOV / (( H / 2 - screenY) - player.yaw * VERT_FOV);
	map->x = map->y * (W / 2 - screenX) / HORI_FOV;
	float rtx = map->y * player.anglecos + map->x * player.anglesin;
	float rtz = map->y * player.anglesin - map->x * player.anglecos;
	map->x = rtx + player.where.x;
	map->y = rtz + player.where.y;
}

void				floor_and_ceiling_texture(t_render *render, t_ab y, t_ab cy)
{
	int tx;
	int ty;
	t_xyz map;
	float mapY;
	t_player	player;
	player = render->player;
	SDL_Surface *curr;

	for (int y = render->ytop[render->x]; y <= render->ybottom[render->x]; ++y)
	{
		if (y >= cy.a1 && y <= cy.b1) //jump to draw floor
		{
			y = cy.b1;
			continue;
		}
		mapY = y < cy.a1 ? render->height_info.yceil : render->height_info.yfloor;
		horz_surf_to_vert(render, mapY, render->x, y, &map);
		//map.x = render->x;
		//map.y = y;
		tx = ((int)(map.x * (CTX_W/ 4)) % CTX_W);
		ty = ((int)(map.y * (CTX_W/ 4)) % CTX_W);

		curr = y > cy.a1 ? render->ftx : render->ctx; // redundant if here
		if (render->light < 1.0)
			((int*)render->surface->pixels)[y * W + render->x] =
				shade_hex_color(((int*)curr->pixels)[ty * CTX_W + tx], render->light);
		else
			((int*)render->surface->pixels)[y * W + render->x] =
				((int*)curr->pixels)[(ty % CTX_W) * CTX_W + (tx % CTX_W)];
	}
}

void		DrawScreen(t_doom *doom)
{
	int			qcurr;
	int			qtotal;
	char		rendered[SECTORNUM];
	t_item		curr;
	t_item		queue[MAXQUEUE];

	qcurr = 0;
	qtotal = qcurr;

	bzero(rendered, (sizeof(char*) * SECTORNUM));
	bzero(doom->ytop, (sizeof(short) * W));
    for (unsigned x = 0; x < W; ++x)
		doom->ybottom[x] = H - 1;

	queue[qtotal++] = (t_item){.sectorno = PLAYER.sector, .sx1 = 0, .sx2 = W - 1};
	while (qcurr < qtotal) // render any other queued sectors
	{
		curr = queue[qcurr++];
		if (rendered[curr.sectorno] > 1)
			continue ;
		draw_sector(doom, queue, &qtotal, curr);
		rendered[curr.sectorno] += 1;
	}
	//exit(1);
}

static inline void		texture_mapping_init(t_doom *doom, t_sector *sect, int s)
{
	doom->u0 = 0;
	doom->u1 = doom->texture[sect->textures[s]]->w;
	//doom->u1 = ft_pythagoras(fabs(sect->vertex[s].x - sect->vertex[s + 1].x),
	//						 fabs(sect->vertex[s].y - sect->vertex[s + 1].y));
	//doom->u1 *= (doom->texture[sect->textures[s]]->w / 6.4);
}

/*
** Render each wall of this sector that is facing towards PLAYER.
*/

static inline int	xd(t_scale viewpoint, int a, int b, int start)
{
   	if (viewpoint.x2 == viewpoint.x1)
		return (a);
	return ((((start - viewpoint.x1) * (b - a)) / (viewpoint.x2 - viewpoint.x1)) + a);
}

void		init_floor_trigon(t_doom *doom, t_scale viewpoint, t_trigon *floor, int *f)
{
	t_xyz a;
	t_xyz b;
	t_xyz c;

	a.x = doom->start_x;
	a.y = xd(viewpoint, HEIGHT_INFO.y.b1, HEIGHT_INFO.y.b2, doom->start_x);
	b.x = doom->end_x;
	b.y = xd(viewpoint, HEIGHT_INFO.y.b1, HEIGHT_INFO.y.b2, doom->end_x);
	c.x = W / 2;
	c.y = H;
	floor[*f] = (t_trigon){.a = a, .b = b, .c = c};
	*f += 1;
}

void		draw_sector(t_doom *doom, t_item *queue, int *qtotal, t_item curr)
{
	int			s;
	t_sector	*sect;
	t_scale		viewpoint;
	t_render	render[W];
	t_trigon	floor[16];
	int			f = 0;

	s = -1;
   	sect = &doom->sectors[curr.sectorno];
	while (++s < sect->npoints)
	{
		rotate_wall_sector(sect, s, &doom->player, &viewpoint);
		if (viewpoint.edges[0].y <= 0 && viewpoint.edges[1].y <= 0)
			continue;
		texture_mapping_init(doom, sect, s);
		if (viewpoint.edges[0].y <= 0 || viewpoint.edges[1].y <= 0)
			player_view_fustrum(doom, &viewpoint);
		player_perspective_tranformation(&viewpoint);
		if (viewpoint.x1 >= viewpoint.x2 || viewpoint.x2 < curr.sx1 ||
				viewpoint.x1 > curr.sx2) // Only render if it's visible
			continue;
		floor_ceiling_heights(doom, sect->neighbors[s], sect, viewpoint);
		render_wall(doom, curr, s, render, viewpoint);

		init_floor_trigon(doom, viewpoint, floor, &f);

		if (sect->neighbors[s] >= 0 && doom->end_x >= doom->start_x)
		{
			queue[*qtotal] = (t_item){.sectorno = sect->neighbors[s],
							.sx1 = doom->start_x, .sx2 = doom->end_x};
			*qtotal += 1;
		}
	}
	printf("%d\n", f);
	while (f--)
		trigon_rasterizer(doom->surface, floor[f].a, floor[f].b, floor[f].c);
	tpool_wait(&doom->tpool);

}

void		floor_ceiling_heights(t_doom *doom, int neighbor, t_sector *sect, t_scale viewpoint)
{
	HEIGHT_INFO.nyceil	= 0;
	HEIGHT_INFO.nyfloor	= 0;
	HEIGHT_INFO.yceil	= sect->ceil	- PLAYER.where.z;
	HEIGHT_INFO.yfloor	= sect->floor	- PLAYER.where.z;
   	if (neighbor >= 0)
  	{
		HEIGHT_INFO.nyceil  = doom->sectors[neighbor].ceil  - PLAYER.where.z;
		HEIGHT_INFO.nyfloor = doom->sectors[neighbor].floor - PLAYER.where.z;
   	}
   	HEIGHT_INFO.y.a1 =	H / 2 - (int)(Yaw(HEIGHT_INFO.yceil, viewpoint.edges[0].y) * viewpoint.yscale1);
	HEIGHT_INFO.y.b1 =	H / 2 - (int)(Yaw(HEIGHT_INFO.yfloor, viewpoint.edges[0].y) * viewpoint.yscale1);
   	HEIGHT_INFO.y.a2 =	H / 2 - (int)(Yaw(HEIGHT_INFO.yceil, viewpoint.edges[1].y) * viewpoint.yscale2);
	HEIGHT_INFO.y.b2 =	H / 2 - (int)(Yaw(HEIGHT_INFO.yfloor, viewpoint.edges[1].y) * viewpoint.yscale2);
   	HEIGHT_INFO.ny.a1 = H / 2 - (int)(Yaw(HEIGHT_INFO.nyceil, viewpoint.edges[0].y) * viewpoint.yscale1);
	HEIGHT_INFO.ny.b1 = H / 2 - (int)(Yaw(HEIGHT_INFO.nyfloor, viewpoint.edges[0].y) * viewpoint.yscale1);
   	HEIGHT_INFO.ny.a2 = H / 2 - (int)(Yaw(HEIGHT_INFO.nyceil, viewpoint.edges[1].y) * viewpoint.yscale2);
	HEIGHT_INFO.ny.b2 = H / 2 - (int)(Yaw(HEIGHT_INFO.nyfloor, viewpoint.edges[1].y) * viewpoint.yscale2);
}

void			draw_portal(t_render *render, t_ab y, t_ab cy)
{
	if (render->texture)
	{
		vline1(render, cy.b2 + 1, cy.b1, G);
		vline1(render, cy.a1, cy.a2 - 1, G);
	}
	else
	{
		t_vline3(render, (t_ab){.a1 = y.a1,	.b1 = y.b1},
						 (t_ab){.a1 = cy.a1, .b1 = y.a2 - 1});
		t_vline3(render, (t_ab){.a1 = y.a1,	.b1 = y.b1},
						 (t_ab){.a1 = cy.b2 + 1, .b1 = cy.b1});
	}
	render->ytop[render->x] = clamp(max(cy.a1, cy.a2), render->ytop[render->x], H - 1);
	render->ybottom[render->x] = clamp(min(cy.b1, cy.b2), 0, render->ybottom[render->x]);
}

static inline int	line_h(t_render *render, int a, int b)
{
   	if (render->x2 == render->x1)
		return (a);
	return ((((render->x - render->x1) * (b - a)) / (render->x2 - render->x1)) + a);
}

static inline void	affine_texture_tranformation(t_doom *doom, int x, int *affine_x, t_scale viewpoint)
{
	float a;
	float b;

	b = (x - viewpoint.x1) * viewpoint.edges[0].y;
   	a = (viewpoint.x2 - x) * viewpoint.edges[1].y;
	if (a == b)
		*affine_x = 0;
	else
		*affine_x = (int)((doom->u0 * a + doom->u1 * b) / (a + b));
}

void		init_thread(t_render *render, int x, t_doom *doom, t_scale viewpoint)
{
	render->x =				x;
	render->surface =		doom->surface;
	render->texture =		doom->key.t;
	render->ytop =			doom->ytop;
	render->ybottom =		doom->ybottom;
	render->player =		doom->player;
	render->height_info =	doom->height_info;
	render->x1 = 			viewpoint.x1;
	render->x2 = 			viewpoint.x2;
	affine_texture_tranformation(doom, x, &render->affine_x, viewpoint);
}

int				thread_render(void *arg)
{
	t_ab		y;		//un clmaped
	t_ab		cy;		//clamped
	t_render	*render;

	render = arg;
   	y.a1 = line_h(render, render->height_info.y.a1, render->height_info.y.a2);
   	y.b1 = line_h(render, render->height_info.y.b1, render->height_info.y.b2);
	cy.a1 = clamp(y.a1, render->ytop[render->x], render->ybottom[render->x]);
	cy.b1 = clamp(y.b1, render->ytop[render->x], render->ybottom[render->x]);
	//ft_circle(render->surface, render->x, y.a1, 10);
	if (render->texture) // || render->ftc == NULL
	{
		vline1(render, render->ytop[render->x], cy.a1 - 1, G);		//ceil
		//vline1(render, cy.b1 + 1, render->ybottom[render->x], 0xb47044);	//floor
	}
	else
		floor_and_ceiling_texture(render, y, cy);
	if (render->neighbor >= 0)
	{
   		y.a2 = line_h(render, render->height_info.ny.a1, render->height_info.ny.a2);
   		y.b2 = line_h(render, render->height_info.ny.b1, render->height_info.ny.b2);
		cy.a2 = clamp(y.a2, render->ytop[render->x], render->ybottom[render->x]);
		cy.b2 = clamp(y.b2, render->ytop[render->x], render->ybottom[render->x]);
		draw_portal(render, y, cy);
	}
	else if (render->texture)
		vline1(render, cy.a1, cy.b1, 0xFFFF00FF);
	else
		t_vline3(render, y, cy);
	return (0);
}

void		render_wall(t_doom *doom, t_item curr, int s, t_render *render, t_scale viewpoint)
{
	int		x;
	int		t;

	t = doom->sectors[curr.sectorno].textures[s];
   	doom->start_x	= max(viewpoint.x1, curr.sx1);		//screen fist wall pixel
	doom->end_x		= min(viewpoint.x2, curr.sx2);		//screen last wall pixel
	x = doom->start_x;
	while (x < doom->end_x)
	{
		init_thread(&render[x], x, doom, viewpoint);
   		render[x].light = doom->sectors[curr.sectorno].light;
		render[x].wtx = doom->texture[t];
		render[x].ctx = doom->texture[0];
		render[x].ftx = doom->texture[1];
		render[x].neighbor = doom->sectors[curr.sectorno].neighbors[s];
		tpool_add(&doom->tpool, thread_render, &render[x]);	
		x += 1;
	}
}
