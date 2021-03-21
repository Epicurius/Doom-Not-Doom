
#include "doom.h"

void	crosshair_position(t_render *render, t_vline *vline, double alpha)
{
	t_wall *wall;
	t_sprite *bh;

	if (!ENABLE_BH)
		return ;
	if (render->player.shooting && render->x == W/2 && vline->y1 == H/2)
	{
		wall = &render->wall;
		if (render->bh->curr >= MAX_BH)
			render->bh->curr = 0;
		bh = &render->bh->num[render->bh->curr];
		bh->pos.x = (vline->alpha / wall->sv2.z) /
			((1 - vline->alpha) / wall->sv1.z + vline->alpha / wall->sv2.z)
				* wall->width;
		bh->pos.y = alpha * wall->height;
		bh->pos.x -= 0.5;
		bh->pos.y -= 0.5;
		bh->ready = 0;
		render->bh->curr += 1;
		if (render->bh->total < MAX_BH)
			render->bh->total += 1;
	}

}
