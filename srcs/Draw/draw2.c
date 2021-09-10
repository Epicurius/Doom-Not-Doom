/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:09:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/10 11:18:33 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Depending on what is in the vertical line send it to the correct function.
 */
static t_vline	draw_vline(t_render *render)
{
	t_vline	vline;

	compute_vline_data(render, render->wall, &vline);
	if (vline.curr.ceiling > render->ytop || vline.curr.floor < render->ybot)
		compute_vline_texels(render, render->wall, &vline);
	draw_floor_and_ceiling(render, &vline);
	if (render->wall->n != -1)
		draw_neighbor_wall(render, &vline);
	else
	{
		vline.y1 = vline.curr.ceiling;
		vline.y2 = vline.curr.floor;
		if (render->wall->wtx == 0 || TEXTURE_DISABLED)
			vline_monochromic(render, &vline, SIDES);
		else if (render->wall->wtx < 0)
			draw_skybox(render, &vline, SIDES);
		else
			draw_wall_texture(render, &vline);
	}
	draw_wsprites(render, &vline);
	draw_wall_bh(render, &vline);
	return (vline);
}

/*
 *	Init render thread.
 */
static t_vline	init_wall_vline(t_render *render, t_sector *sector, int s)
{
	t_wall	*wall;

	wall = sector->wall[s];
	render->wall = wall;
	render->wsprite = &wall->wsprite;
	render->floor = &sector->floor;
	render->ceiling = &sector->ceiling;
	render->bullet_hole = &wall->bullet_hole;
	render->light = sector->light;
	render->s = s;
	return (draw_vline(render));
}

/*
 *	Loops through all the walls in the sector until it finds the visible one.
 *	Then draws the wall, floor, ceiling, wall sprites, bullet holes.
 *	If wall not solid recall render_vline with neighbour sector until it is.
 *	Then loop back and check for each wall if it has a portal texture.
 *	If it has draw it.
 */
static int	render_vline(t_render render, int sector)
{
	int			s;
	t_sector	*sect;
	t_vline		vline;

	s = -1;
	sect = &render.sectors[sector];
	while (++s < sect->npoints)
	{
		if (!sect->wall[s]->visible)
			continue ;
		if (render.x < sect->wall[s]->cx1 || render.x > sect->wall[s]->cx2)
			continue ;
		sect->visible = TRUE;
		vline = init_wall_vline(&render, sect, s);
		if (sect->wall[s]->n == -1)
			return (1);
		render_vline(render, sect->wall[s]->n);
		if (sect->wall[s]->ptx > 0)
			draw_portal_texture(&render, &vline);
		return (1);
	}
	return (1);
}

/*
 *	Loop through vertical line and for each finds there sector.
 *	Then passes the vertical line to render_vline.
 */
static int	loop_screen_sector(void	*arg)
{
	t_render	*render;
	t_v3		pos;
	double		tmp;
	t_player	*p;

	render = arg;
	p = render->player;
	while (render->x < render->xend)
	{
		render->ytop = 0;
		render->ybot = render->surface->h - 1;
		tmp = (render->x / (double)(render->surface->w - 1))
			* render->cam->range + render->cam->near_left;
		pos.x = tmp * (-p->anglesin) - (-NEAR_Z) * p->anglecos + p->where.x;
		pos.y = tmp * p->anglecos - (-NEAR_Z) * p->anglesin + p->where.y;
		pos.z = p->where.z + p->eyelvl;
		render_vline(*render,
			find_sector(render->sectors, render->nb_sectors, pos));
		render->x++;
	}
	return (1);
}

/*
 *	Splits the surface in thread amount of pieces and adds the to tpool.
 */
void	draw_map(t_doom *doom)
{
	int	x;
	int	w;

	x = -1;
	w = doom->surface->w;
	while (++x < doom->nb.threads)
	{
		doom->render[x].x = w / (double)doom->nb.threads * x;
		doom->render[x].xend = ft_min(
				w / (double)doom->nb.threads * (x + 1), w);
		tpool_add(&doom->tpool, loop_screen_sector, &doom->render[x]);
	}
}
