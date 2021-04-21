
#include "doom.h"

void	reset_bh_dynamic(t_doom *doom)
{
	int i;
	int j;
	t_sector *sect;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		if (doom->sectors[i].visible)
			continue ;
		sect = &doom->sectors[i];
		j = -1;
		while (++j < sect->npoints)
		{
			sect->wall[j]->bh.total = 0;
			sect->wall[j]->bh.curr = 0;
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
