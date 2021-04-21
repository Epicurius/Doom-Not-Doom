
#include "doom.h"

/*
typedef struct	s_reset_array
{
	int		start;
	int		end;
	double	*zbuffer;
	int		*ytop;
	int		*ybot;
}		t_reset_array;

int	reset_zbuffer_thread(void *arg)
{
	int x;
	int y;
	int end;
	double *zbuffer;
	int		*ytop;
	int		*ybot;

	x = ((t_reset_array*)arg)->start;
	end = ((t_reset_array*)arg)->end;
	zbuffer = ((t_reset_array*)arg)->zbuffer;
	ytop = ((t_reset_array*)arg)->ytop;
	ybot = ((t_reset_array*)arg)->ybot;
	while (x < end)
	{
		ytop[x] = 0;
		ybot[x] = H;
		y = -1;
		while (++y < H)
			zbuffer[y * W + x] = RENDER_DISTANCE;
		x++;
	}
	return (1);
}

void	reset_render_utils1(t_doom *doom)
{
	int i;
	t_reset_array arr[doom->nb.processors];

	i = -1;
	while (++i < doom->nb.processors)
	{
		arr[i].start = W / (float)doom->nb.processors * i;
		arr[i].end = W / (float)doom->nb.processors * (i + 1);
		arr[i].zbuffer = doom->zbuffer;
		arr[i].ytop = doom->ytop;
		arr[i].ybot = doom->ybot;
		tpool_add(&doom->tpool, reset_zbuffer_thread, &arr[i]);
	}
//	tpool_wait(&doom->tpool);
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
}*/
