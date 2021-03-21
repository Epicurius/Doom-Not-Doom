
#include "doom.h"

void	draw_floor_and_ceiling(t_render *render, t_vline *vline)
{
	vline->height.ceiling = vline->max.ceiling - render->ceiling.head;
	vline->height.floor = render->floor.feet - vline->max.floor;

	if (vline->height.ceiling > render->ytop[render->x])
	{
		vline->y1 = render->ytop[render->x];
		vline->y2 = min(vline->curr.ceiling, render->ybot[render->x]);
		if (render->ceiling.tx == -1)
			vline_color(render, vline, 0xFF888888);
		else if (render->ceiling.tx == 0)
			draw_skybox(render, vline, TOP);
		else
			draw_ceiling_texture(render, vline);
	}
	if (vline->curr.floor < render->ybot[render->x])
	{
		vline->y1 = max(0, vline->curr.floor);
		vline->y2 = render->ybot[render->x];
		if (render->floor.tx == -1)
			vline_color(render, vline, 0xFF888888);
		else if (render->floor.tx == 0)
			draw_skybox(render, vline, BOT);
		else
			draw_floor_texture(render, vline);
	}
}
