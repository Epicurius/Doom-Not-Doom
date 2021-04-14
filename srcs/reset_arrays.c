
#include "doom.h"

void	reset_render_arrays(t_doom *doom)
{
	int i;

	i = -1;
	while (++i < W)
	{
		doom->ytop[i] = 0;
		doom->ybot[i] = H;
	}
	i = -1;
	t_sector *sect;
	while (++i < doom->nb.sectors)
	{
		if (doom->sectors[i].visible)
			continue ;
		sect = &doom->sectors[i];
		int w = -1;
		while (++w < sect->npoints)
		{
			sect->wall[w]->bh.total = 0;
			sect->wall[w]->bh.curr = 0;
		}
	}
}

void	reset_bh(t_doom *doom)
{
	int i;

	i = -1;
	while (++i < doom->nb.walls)
	{
		doom->walls[i].bh.total = 0;
		doom->walls[i].bh.curr = 0;
	}
	
}
