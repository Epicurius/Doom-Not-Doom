/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:09:28 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/26 15:17:06 by nneronin         ###   ########.fr       */
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

static inline void	horz_surf_to_vert(t_render *render, float Hight, float screenX, int screenY,
					float pitch, t_xyz *t)
{
	float		x;
	float		z;
	t_player	player;

	player = render->player;
	// (Sector Height) / ((distance from player (z)) - (player Y view))
	// Height / ((H/2 - screenX) - pitch)
	z = Hight / (-screenY + pitch);
	x = z * screenX;
	//3D map cordinates to 2D
	t->x = (z * player.anglesin - x * player.anglecos) + player.where.y;
	t->y = (z * player.anglecos + x * player.anglesin) + player.where.x;
	//Map cordinates adjusted to texture
	t->x = ((int)(t->x * 256) % CTX_W);
	t->y = ((int)(t->y * 256) % CTX_W); // T/4
}

void				floor_and_ceiling_texture(t_render *render, t_ab y, t_ab cy)
{
	t_xyz		t;
	float		sect_y;
	float		pitch = H/2 - (render->player.pitch * VERT_FOV);
	float 		screenX = ((W/2 - render->x) / HORI_FOV);
	SDL_Surface	*curr;

	curr = render->ctx;
	sect_y = render->height_info.yceil * VERT_FOV;

	int y1 = render->ytop[render->x];
	while (y1 < render->ybot[render->x])
	{
		if (y1 >= cy.a1 && y1 <= cy.b1) //jump to floor start_y
		{
			y1 = cy.b1;
			if (y1 >= render->ybot[render->x])
				return ;
			sect_y = render->height_info.yfloor * VERT_FOV;
			curr = render->ftx;
			break ;
		}
		//horz_surf_to_vert(render, sect_y, screenX, y1, pitch, &t);
		int y = abs((int)(y1 + render->player.pitch * VERT_FOV)) % CTX_W;
		int x = abs((int)(render->x + render->player.yaw * HORI_FOV)) % CTX_W;
		doom_pixel_copy(render, ((int*)curr->pixels)[y * CTX_W + x],
			y1 * W + render->x);
		y1 += 1;
	}
	while (y1 < render->ybot[render->x])
	{
		horz_surf_to_vert(render, sect_y, screenX, y1, pitch, &t);
		doom_pixel_copy(render, ((int*)curr->pixels)[(int)t.y * CTX_W + (int)t.x],
			y1 * W + render->x);
		y1 += 1;
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
	memset(doom->pz, 0, (W*H)*sizeof(*doom->pz));
    	//for (unsigned x = 0; x < W * H; ++x)
	//	((int*)doom->surface->pixels)[x] = 0x000000;
    	for (unsigned x = 0; x < W; ++x)
		doom->ytop[x] = 0, doom->ybot[x] = H;

	queue[qtotal++] = (t_item){.sectorno = PLAYER.sector, .sx1 = 0, .sx2 = W};
    	for (unsigned x = 0; x < SECTORNUM; ++x)
		rendered[x] = 0;
	while (qcurr < qtotal)
	{
		curr = queue[qcurr++];
		if (rendered[curr.sectorno] > 1)
			continue;
		draw_sector(doom, queue, &qtotal, curr);
		rendered[curr.sectorno] += 1;
	}
}

static inline void		texture_mapping_init(t_doom *doom, t_sector *sect, int s)
{
	doom->u0 = 0;
	doom->u1 = doom->texture[sect->textures[s]]->w - 1;
	//doom->u1 = ft_pythagoras(fabs(sect->vertex[s].x - sect->vertex[s + 1].x),
	//		fabs(sect->vertex[s].y - sect->vertex[s + 1].y));
	//doom->u1 *= (doom->texture[sect->textures[s]]->w / 6.4);
}

/*
** Render each wall of this sector that is facing towards PLAYER.
*/
void		draw_sector(t_doom *doom, t_item *queue, int *qtotal, t_item curr)
{
	int			s;
	t_sector	*sect;
	t_scale		viewpoint;
	t_render	render[W];
	
	s = -1;
   	sect = &doom->sectors[curr.sectorno];
	render_entity(doom, curr);
	//SDL_UpdateWindowSurface(doom->win), SDL_Delay(200);
	while (++s < sect->npoints)
	{
		rotate_wall_sector(sect, s, &doom->player, &viewpoint);
		if (viewpoint.edges[0].y <= 0 && viewpoint.edges[1].y <= 0)
			continue ;
		texture_mapping_init(doom, sect, s);
		if (viewpoint.edges[0].y <= 0 || viewpoint.edges[1].y <= 0)
			player_view_fustrum(doom, &viewpoint); //clip
		player_perspective_tranformation(&viewpoint);
		if (viewpoint.x1 >= viewpoint.x2 ||viewpoint.x2 < curr.sx1 ||
				viewpoint.x1 > curr.sx2) // Only render if it's visible
			continue ;
		floor_ceiling_heights(doom, sect->neighbors[s], sect, viewpoint);
		render_wall(doom, curr, s, render, viewpoint);
		if (sect->neighbors[s] >= 0 && sect->neighbors[s] != PLAYER.sector &&
			doom->end_x > doom->start_x) //>=
		{
			queue[*qtotal] = (t_item){sect->neighbors[s], doom->start_x, doom->end_x};
			*qtotal += 1;
		}
	}
	tpool_wait(&doom->tpool);	
	//SDL_UpdateWindowSurface(doom->win), SDL_Delay(200);
	//render_entity(doom, curr);
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
   	HEIGHT_INFO.y.a1 = H / 2 - (int)(Yaw(HEIGHT_INFO.yceil, viewpoint.edges[0].y) * viewpoint.yscale1);
	HEIGHT_INFO.y.b1 = H / 2 - (int)(Yaw(HEIGHT_INFO.yfloor, viewpoint.edges[0].y) * viewpoint.yscale1);
   	HEIGHT_INFO.y.a2 = H / 2 - (int)(Yaw(HEIGHT_INFO.yceil, viewpoint.edges[1].y) * viewpoint.yscale2);
	HEIGHT_INFO.y.b2 = H / 2 - (int)(Yaw(HEIGHT_INFO.yfloor, viewpoint.edges[1].y) * viewpoint.yscale2);
   	HEIGHT_INFO.ny.a1 = H / 2 - (int)(Yaw(HEIGHT_INFO.nyceil, viewpoint.edges[0].y) * viewpoint.yscale1);
	HEIGHT_INFO.ny.b1 = H / 2 - (int)(Yaw(HEIGHT_INFO.nyfloor, viewpoint.edges[0].y) * viewpoint.yscale1);
   	HEIGHT_INFO.ny.a2 = H / 2 - (int)(Yaw(HEIGHT_INFO.nyceil, viewpoint.edges[1].y) * viewpoint.yscale2);
	HEIGHT_INFO.ny.b2 = H / 2 - (int)(Yaw(HEIGHT_INFO.nyfloor, viewpoint.edges[1].y) * viewpoint.yscale2);
}

void			draw_portal(t_render *render, t_ab y, t_ab cy)
{
	if (render->texture)
	{
		vline1(render, cy.a1, cy.a2, G);
		vline1(render, cy.b2, cy.b1, G);
	}
	else
	{
		//make separate func for these
		t_vline3(render, (t_ab){.a1 = y.a1,	.b1 = y.b1}, (t_ab){.a1 = cy.a1, .b1 = y.a2});
		t_vline3(render, (t_ab){.a1 = y.a1,	.b1 = y.b1}, (t_ab){.a1 = cy.b2, .b1 = cy.b1});
	}
	render->ytop[render->x] = clamp(max(cy.a1, cy.a2), render->ytop[render->x], H);
	render->ybot[render->x] = clamp(min(cy.b1, cy.b2), 0, render->ybot[render->x]);
}

/*
** Inerpolate line
*/
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
	render->ytop =	doom->ytop;
	render->ybot =	doom->ybot;
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
	cy.a1 = clamp(y.a1, render->ytop[render->x], render->ybot[render->x]);
	cy.b1 = clamp(y.b1, render->ytop[render->x], render->ybot[render->x]);
	if (render->texture) // || render->ftc == NULL
	{
		vline1(render, render->ytop[render->x], cy.a1, G);		//ceil
		vline1(render, cy.b1, render->ybot[render->x], 0xb47044);	//floor
	}
	else
		floor_and_ceiling_texture(render, y, cy);
	if (render->neighbor >= 0)
	{
   		y.a2 = line_h(render, render->height_info.ny.a1, render->height_info.ny.a2);
   		y.b2 = line_h(render, render->height_info.ny.b1, render->height_info.ny.b2);
		cy.a2 = clamp(y.a2, render->ytop[render->x], render->ybot[render->x]);
		cy.b2 = clamp(y.b2, render->ytop[render->x], render->ybot[render->x]);
		draw_portal(render, y, cy);
	}
	else if (render->texture)
		vline1(render, cy.a1, cy.b1, 0xFF888888);
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
	doom->end_x	= min(viewpoint.x2, curr.sx2);		//screen last wall pixel
	x = doom->start_x;
	while (x < doom->end_x)
	{
		init_thread(&render[x], x, doom, viewpoint);
   		render[x].light = doom->sectors[curr.sectorno].light;
		render[x].wtx = doom->texture[t];
		render[x].ctx = doom->texture[0];
		render[x].ftx = doom->texture[1];
		render[x].neighbor = doom->sectors[curr.sectorno].neighbors[s];
		//thread_render(&render[x]);
		tpool_add(&doom->tpool, thread_render, &render[x]);
		x += 1;
	}
	//SDL_UpdateWindowSurface(doom->win);
}
