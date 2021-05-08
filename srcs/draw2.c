/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:09:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/05 11:40:45 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	compute_vline_data(t_render *render, t_wall wall, t_vline *vline)
{
	vline->alpha = (render->x - wall.x1) / wall.xrange;
	vline->clipped_alpha = (render->x - wall.cx1) / (wall.cx2 - wall.cx1);
	vline->divider = 1 / (wall.sv2.z + vline->alpha * wall.zrange);
	vline->z = wall.zcomb * vline->divider;
	vline->z_near_z = vline->z * NEAR_Z;
	vline->max.ceiling = vline->clipped_alpha * wall.range.ceiling + wall.s1.ceiling;
	vline->curr.ceiling = ft_clamp(vline->max.ceiling,
				render->ytop, render->ybot);
	vline->max.floor = vline->clipped_alpha * wall.range.floor + wall.s1.floor;
	vline->curr.floor = ft_clamp(vline->max.floor,
				render->ytop, render->ybot);
	vline->line_height = (vline->clipped_alpha * wall.range.floor + wall.s1.floor)
				- (vline->clipped_alpha * wall.range.ceiling + wall.s1.ceiling);
}

void	compute_vline_texels(t_render *render, t_wall wall, t_vline *vline)
{
	t_xyz camera_z;

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

t_vline		draw_vline(t_render *render)
{
	t_vline		vline;

	compute_vline_data(render, render->wall, &vline);
	if (vline.curr.ceiling > render->ytop || vline.curr.floor < render->ybot)
			compute_vline_texels(render, render->wall, &vline);
	draw_floor_and_ceiling(render, &vline);
	if (render->wall.n != -1)
		draw_neighbor_wall(render, &vline);
	else
	{
		vline.y1 = vline.curr.ceiling;
		vline.y2 = vline.curr.floor;
		if (render->wall.wtx == 0 || TEXTURE_DISABLED)
			vline_monochromic(render, &vline);
		else if (render->wall.wtx < 0)
			draw_skybox(render, &vline, SIDES);
		else
			draw_wall_texture(render, &vline);
	}
	draw_wsprites(render, &vline);
	draw_wall_bh(render, &vline);
	return (vline);
}

t_vline 	render_wall_vline(t_render *render, t_sector *sector, int s)
{
	t_wall		*wall;

	wall = sector->wall[s];
	wall->visible 	= 1;

	render->wall		= *wall;
	render->wsprite		= wall->wsprite;
	render->floor		= sector->floor;
	render->ceiling		= sector->ceiling;

	render->bh			= &wall->bh;
	
	render->light		= sector->light;
	render->s			= s;
	//draw_vline(render);
	return (draw_vline(render));
}

int		render_vline(t_render render, int sector)
{
	int	s;
	t_sector *sect;
	t_vline vline;

	s = -1;
   	sect = &render.sectors[sector];
	while (++s < sect->npoints)
	{
		if (!sect->wall[s]->visible)
			continue ;
		if (render.x < sect->wall[s]->cx1 || render.x > sect->wall[s]->cx2)
			continue ;
		sect->visible = 1;
		vline = render_wall_vline(&render, sect, s);
		if (sect->wall[s]->n == -1)
			return (1);
		render_vline(render, sect->wall[s]->n);
		if (sect->wall[s]->ptx != -1)
			draw_portal_texture(&render, &vline);
		return (1);
	}
	return (1);
}

int		loop_screen_sector(void	*arg)
{
	t_render *render;

	render = arg;
	while (render->x < render->xend)
	{
		render->ytop = 0;
		render->ybot = render->surface->h;
		render_vline(*render, render->fustrum[render->x]);
		render->x++;
	}
	return (1);
}

void		screen_x_sector(t_doom *doom, int x, int xend)
{
	t_xyz pos;
	t_player p;
	double tmp;
	
	p = doom->player;
	while (x < xend)
	{
		tmp = (x / (double)(doom->surface->w - 1)) * doom->cam.range + doom->cam.near_left;
		pos.x = tmp * (-p.anglesin) - (-doom->cam.near_z) * p.anglecos + p.where.x;
		pos.y = tmp * p.anglecos - (-doom->cam.near_z) * p.anglesin + p.where.y;
		//pos.z = p.where.z + EYE_LVL;
		doom->fustrum[x] = find_sector(doom, pos);
		x++;
	}
}

void		DrawScreen(t_doom *doom)
{
	int x;
	int w;

	x = -1;
	w = doom->surface->w;
	while (++x < doom->nb.threads)
	{
		doom->render[x].x = w /(double)doom->nb.threads * x;
		doom->render[x].xend = ft_min(w /(double)doom->nb.threads * (x + 1), w);
		screen_x_sector(doom, doom->render[x].x, doom->render[x].xend);
		doom->render[x].player = doom->player;
		tpool_add(&doom->tpool, loop_screen_sector, &doom->render[x]);
	}
}
