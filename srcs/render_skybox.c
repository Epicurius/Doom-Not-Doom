
#include "doom.h"

void	compute_vline_data(t_render *render, t_wall wall, t_vline *vline)
{
	vline->alpha = (render->x - wall.x1) / wall.xrange;
	vline->clipped_alpha = (render->x - wall.cx1) / wall.clipped_xrange;
	vline->divider = 1 / (wall.sv2.z + vline->alpha * wall.zrange);
	vline->z = wall.zcomb * vline->divider;
	vline->z_near_z = vline->z * NEAR_Z;
	vline->max_ceiling = vline->clipped_alpha * wall.range.ceiling + wall.s1.ceiling;
	vline->curr.ceiling = clamp(vline->max_ceiling,
				render->ytop[render->x], render->ybot[render->x]);
	vline->max_floor = vline->clipped_alpha * wall.range.floor + wall.s1.floor;
	vline->curr.floor = clamp(vline->max_floor,
				render->ytop[render->x], render->ybot[render->x]);
	vline->start.ceiling = vline->max_ceiling - wall.ceiling_horizon;
	vline->start.floor = vline->max_floor - wall.floor_horizon;

	vline->line_height = (vline->clipped_alpha * wall.range.floor + wall.s1.floor)
				- (vline->clipped_alpha * wall.range.ceiling + wall.s1.ceiling);
}

void	precompute_texels(t_render *render, t_wall wall, t_vline *vline)
{
	vline->texel.x = (wall.x0z1 + vline->alpha * wall.xzrange) * vline->divider;
	vline->texel.y = (wall.y0z1 + vline->alpha * wall.yzrange) * vline->divider;
	vline->texel_x_near_z = vline->texel.x * NEAR_Z;
	vline->texel_y_near_z = vline->texel.y * NEAR_Z;
	vline->camera_x_z = render->player_pos.x * vline->z;
	vline->camera_y_z = render->player_pos.y * vline->z;
	vline->texel_x_camera_range = vline->camera_x_z - vline->texel_x_near_z;
	vline->texel_y_camera_range = vline->camera_y_z - vline->texel_y_near_z;
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
	if (render->neighbor != -1)
		draw_neighbor_wall(render, &vline);
	else
	{	vline.y1 = (int)(vline.curr.ceiling);
		vline.y2 = (int)(vline.curr.floor);
		if (render->texture)
			vline_color(render, &vline, 0xFF888888);
		else
			draw_wall_texture(render, &vline);
	}
	return (0);
}
