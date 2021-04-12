
#include "doom.h"


typedef struct	s_reset_array
{
	int	start;
	int	end;
	void	*array;
}		t_reset_array;

int	reset_zbuffer_thread(void *arg)
{
	int start;
	int end;
	double *zbuffer;
	//Uint32 *pixels;

	start = ((t_reset_array*)arg)->start;
	end = ((t_reset_array*)arg)->end;
	zbuffer = ((t_reset_array*)arg)->array;
	//pixels = ((t_reset_array*)arg)->array2;
	while (start < end)
		zbuffer[start++] = RENDER_DISTANCE;//, pixels[start++] = 0x000000;
	return (0);
}

void	reset_render_arrays(t_doom *doom)
{
	int i;
/*
#ifndef JONY
	t_reset_array arr[doom->nb.processors];

	i = -1;
	// dont reset force map to put pixel
	while (++i < doom->nb.processors)
	{
		arr[i].start = W * H / (float)doom->nb.processors * i;
		arr[i].end = W * H / (float)doom->nb.processors * (i + 1);
		arr[i].array = doom->zbuffer;
		//arr[i].array2 = doom->surface->pixels;
		tpool_add(&doom->tpool, reset_zbuffer_thread, &arr[i]);
	}
#else
	i = -1;
	while (++i < W * H)
		doom->zbuffer[i] = RENDER_DISTANCE;
#endif
*/
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
#ifndef JONY
	//tpool_wait(&doom->tpool);
#endif
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
