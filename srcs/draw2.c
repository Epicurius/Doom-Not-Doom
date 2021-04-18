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

void		DrawScreen(t_doom *doom)
{
	int		qcurr;
	int		qtotal;
	t_item		curr;
	t_item		queue[MAXQUEUE];

	qcurr = 0;
	qtotal = qcurr;
	queue[0] = (t_item){.sectorno = -2, .sx1 = 0, .sx2 = W};
	find_start_sectors(doom, queue, &qtotal);
	while (qcurr < qtotal)
	{
		curr = queue[qcurr++];
		draw_sector(doom, queue, &qtotal, curr);
	}
}

/*
** Render each wall of this sector that is facing towards PLAYER.
*/
void		draw_sector(t_doom *doom, t_item *queue, int *qtotal, t_item curr)
{
	int	s;
	t_sector	*sect;
	t_render	render[W];
	
	s = -1;
   	sect = &doom->sectors[curr.sectorno];
	while (++s < sect->npoints)
	{
		if (!sect->wall[s]->visible)
			continue ;
		sect->visible = 1;
		render_wall(doom, curr, s, render, sect->wall[s]);
		if (sect->wall[s]->n != -1 && doom->end_x > doom->str_x)
		{
			queue[*qtotal] = (t_item){sect->wall[s]->n,
				doom->str_x, doom->end_x};
			*qtotal += 1;
		}
	}
	if (!tpool_wait(&doom->tpool))
		return ;
}


void	compute_vline_data(t_render *render, t_wall wall, t_vline *vline)
{
	vline->alpha = (render->x - wall.x1) / wall.xrange;
	vline->clipped_alpha = (render->x - wall.cx1) / (wall.cx2 - wall.cx1);
	vline->divider = 1 / (wall.sv2.z + vline->alpha * wall.zrange);
	vline->z = wall.zcomb * vline->divider;
	vline->z_near_z = vline->z * NEAR_Z;
	vline->max.ceiling = vline->clipped_alpha * wall.range.ceiling + wall.s1.ceiling;
	vline->curr.ceiling = ft_clamp(vline->max.ceiling,
				render->ytop[render->x], render->ybot[render->x]);
	vline->max.floor = vline->clipped_alpha * wall.range.floor + wall.s1.floor;
	vline->curr.floor = ft_clamp(vline->max.floor,
				render->ytop[render->x], render->ybot[render->x]);
	vline->line_height = (vline->clipped_alpha * wall.range.floor + wall.s1.floor)
				- (vline->clipped_alpha * wall.range.ceiling + wall.s1.ceiling);
}

void	precompute_texels(t_render *render, t_wall wall, t_vline *vline)
{
	t_v2 camera_z;

	camera_z.x = render->player.where.x * vline->z;
	camera_z.y = render->player.where.y * vline->z;
	vline->texel.x = (wall.x0z1 + vline->alpha * wall.xzrange) * vline->divider;
	vline->texel.y = (wall.y0z1 + vline->alpha * wall.yzrange) * vline->divider;
	vline->texel_nearz.x = vline->texel.x * NEAR_Z;
	vline->texel_nearz.y = vline->texel.y * NEAR_Z;
	vline->texel_range.x = camera_z.x - vline->texel_nearz.x;
	vline->texel_range.y = camera_z.y - vline->texel_nearz.y;
	vline->zrange = vline->z - NEAR_Z;
}

int		draw_vline(void	*arg)
{
	t_vline		vline;
	t_render	*render;

	render = arg;
	compute_vline_data(render, render->wall, &vline);
	if (vline.curr.ceiling > render->ytop[render->x] ||
		vline.curr.floor < render->ybot[render->x])
			precompute_texels(render, render->wall, &vline);
	draw_floor_and_ceiling(render, &vline);
	if (render->wall.n != -1)
		draw_neighbor_wall(render, &vline);
	else
	{	vline.y1 = vline.curr.ceiling;
		vline.y2 = vline.curr.floor;
		if (render->wall.wtx == -1)
			vline_color(render, &vline, 0xFF888888);
		else if (render->wall.wtx == 0)
			draw_skybox(render, &vline, SIDES);
		else
			draw_wall_texture(render, &vline);
	}
	draw_wsprites(render, &vline);
	if (ENABLE_BH)
		draw_wall_bh(render, &vline);
	return (1);
}

void		render_wall(t_doom *doom, t_item curr, int s, t_render *render, t_wall *wall)
{
	int		x;
	t_sector	sector;

	wall->visible 	= 1;
   	doom->str_x	= max(wall->cx1, curr.sx1);		//screen fist wall pixel
	doom->end_x	= min(wall->cx2, curr.sx2);		//screen last wall pixel

	x = doom->str_x;
   	sector = doom->sectors[curr.sectorno];
	while (x < doom->end_x)
	{
		// Actual
		render[x].surface =	doom->surface;
		render[x].ytop =	doom->ytop;
		render[x].ybot =	doom->ybot;

		render[x].stx =		doom->stx;
		render[x].mtx =		doom->mtx;

		render[x].bh =		&wall->bh;
		render[x].clock =	doom->clock;
		render[x].wsprite =	&wall->wsprite;
	
		// Copy
		render[x].player =	doom->player;
		render[x].wall =	*wall;
		render[x].floor =	sector.floor;
		render[x].ceiling =	sector.ceiling;
		
		render[x].skybox =	doom->skybox;
   		render[x].light =	sector.light;
		render[x].x =		x;
		render[x].s =		s;
		tpool_add(&doom->tpool, draw_vline, &render[x]);
		//draw_vline(&render[x]);
		x += 1;
	}
}
//Threading add is 0.33% faster
//Making copy of wall saves 4 fps
