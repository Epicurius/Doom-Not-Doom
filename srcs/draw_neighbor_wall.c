
#include "doom.h"

void	draw_neighbor_wall(t_render *render, t_vline *vline)
{
	vline->max_n.ceiling = vline->clipped_alpha *
		render->wall.range_n.ceiling + render->wall.s1_n.ceiling;
	vline->max_n.floor = vline->clipped_alpha *
		render->wall.range_n.floor + render->wall.s1_n.floor;
	vline->curr_n.ceiling = clamp(vline->max_n.ceiling,
		render->ytop[render->x], render->ybot[render->x]);
	vline->curr_n.floor = clamp(vline->max_n.floor,
		render->ytop[render->x], render->ybot[render->x]);

	if (vline->curr_n.ceiling > vline->curr.ceiling)
	{
		vline->y1 = vline->curr.ceiling;
		vline->y2 = vline->curr_n.ceiling;
		if (render->wall.wtx == -1)
			vline_color(render, vline, 0xFF666666);
		else if (render->wall.wtx == 0)
			draw_skybox(render, vline, TOP_HALF);
		else
			draw_wall_texture(render, vline);
	}
	if (vline->curr_n.floor < vline->curr.floor)
	{
		vline->y1 = vline->curr_n.floor;
		vline->y2 = vline->curr.floor;
		if (render->wall.wtx == -1)
			vline_color(render, vline, 0xFF666666);
		else if (render->wall.wtx == 0)
			draw_skybox(render, vline, BOT_HALF);
		else
			draw_wall_texture(render, vline);
	}
	
	render->ytop[render->x] = clamp(max(vline->curr_n.ceiling,
	vline->curr.ceiling), render->ytop[render->x], render->ybot[render->x]);

	render->ybot[render->x] = clamp(min(vline->curr_n.floor,
	vline->curr.floor), render->ytop[render->x], render->ybot[render->x]);

	if (render->wall.ptx >= 0)
	{
		vline->y1 = render->ytop[render->x]; 
		vline->y2 = render->ybot[render->x]; 
		draw_portal_texture(render, vline);
	}
}
