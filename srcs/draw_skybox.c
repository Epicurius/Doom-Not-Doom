
#include "doom.h"


void	skybox_limits(t_render *render, t_vline *vline, int side, t_limits *limit)
{
	if (side == TOP)
	{
		limit->min = render->ytop;
		limit->max = vline->curr.ceiling;
	}
	else if (side == BOT)
	{
		limit->min = vline->curr.floor;
		limit->max = render->ybot;
	}
	else if (side == SIDES)
	{
		limit->min = vline->curr.ceiling;
		limit->max = vline->curr.floor;
	}
	else if (side == TOP_HALF)
	{
		limit->min = vline->curr.ceiling;
		limit->max = vline->curr_n.ceiling;
	}
	else if (side == BOT_HALF)
	{
		limit->min = vline->curr_n.floor;
		limit->max = vline->curr.floor;
	}
	else
		printf("ERROR %d\n", side);
}

void	draw_skybox_vline(t_render *render, t_vline skybox, int texture_w, t_limits limit)
{
	if (limit.min < skybox.curr.ceiling)
	{
		skybox.y1 = limit.min;
		skybox.y2 = min(skybox.curr.ceiling, limit.max);
		skybox_ceiling_vline(render, skybox);
	}
	if (skybox.curr.ceiling < limit.max)
	{
		skybox.y1 = max(limit.min, skybox.curr.ceiling);
		skybox.y2 = min(skybox.curr.floor, limit.max);
		skybox_wall_vline(render, skybox, texture_w);
	}
	if (skybox.curr.floor < limit.max)
	{
		skybox.y1 = max(limit.min, skybox.curr.floor);
		skybox.y2 = limit.max;
		skybox_floor_vline(render, skybox);
	}

}

void	compute_skybox_vline_data(t_render *render, t_vline *vline, int i)
{
	t_wall wall;

	wall = render->skybox[i];
	vline->alpha = (render->x - wall.x1) / wall.xrange;
	vline->clipped_alpha = (render->x - wall.cx1) / (wall.cx2 - wall.cx1);
	vline->z = 1.0 / ((1.0 - vline->alpha) / wall.sv1.z + vline->alpha / wall.sv2.z);
	vline->divider = 1 / (wall.sv2.z + vline->alpha * wall.zrange);
	vline->z = wall.zcomb * vline->divider;
	vline->texel.x = (wall.x0z1 + vline->alpha * wall.xzrange) * vline->divider;
	vline->texel.y = (wall.y0z1 + vline->alpha * wall.yzrange) * vline->divider;
	vline->max.ceiling = vline->clipped_alpha * wall.range.ceiling + wall.s1.ceiling;
	vline->curr.ceiling = ft_clamp(vline->max.ceiling,render->ytop, render->ybot);
	vline->max.floor = vline->clipped_alpha * wall.range.floor + wall.s1.floor;
	vline->curr.floor = ft_clamp(vline->max.floor, render->ytop, render->ybot);
	vline->start.ceiling = vline->max.ceiling - render->player.horizon;
	vline->start.floor = vline->max.floor - render->player.horizon;
	vline->line_height = (vline->clipped_alpha * wall.range.floor + wall.s1.floor)
				- (vline->clipped_alpha * wall.range.ceiling + wall.s1.ceiling);
}

void	draw_skybox(t_render *render, t_vline *vline, int side)
{
	t_vline		skybox;
	t_limits	limit;
	int		texture_w;

	int i = -1;
	while (++i < 4)
	{
		if (!render->skybox[i].visible ||
			render->skybox[i].cx1 >= render->skybox[i].cx2 ||
			render->skybox[i].cx1 > render->x ||
			render->skybox[i].cx2 < render->x)
			continue ;
		//skybox.z_near_z  = vline->z_near_z;
		skybox_limits(render, vline, side, &limit);
		compute_skybox_vline_data(render, &skybox, i);
		texture_w = 1024 / (render->skybox[i].sv2.z ?
			render->skybox[i].sv2.z : render->skybox[i].cv2.z);
		render->s = i;
		draw_skybox_vline(render, skybox, texture_w, limit);
	}
}
