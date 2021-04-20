
#include "doom.h"

int		partition_screen(t_doom *doom, int *fustrum, t_item *queue, int *qtotal)
{
	int	x;
	int	i;

	x = -1;
	while (++x < W)
	{
		i = 0;
		int sector = fustrum[x];
		while (i < doom->nb.sectors && i < *qtotal && queue[i].sectorno != sector)
			i++;
		if (i < doom->nb.sectors && queue[i].sectorno != sector && sector != -1)
		{
			queue[i].sectorno = sector;
			queue[i].sx1 = x;
			*qtotal += 1;
		}
		else if (i < doom->nb.sectors && queue[i].sectorno == sector)
			queue[i].sx2 = x;
	}
	return (0);
}

typedef struct	s_fustrum_thread
{
	int	x;
	int	end;
	int	*fustrum;
	t_doom	*doom;
}		t_fustrum_thread;

int	fustrum_in_sector(void *arg)
{
	int	x;
	int	end;
	t_xyz	pos;
	t_player p;

	x = ((t_fustrum_thread*)arg)->x;
	end = ((t_fustrum_thread*)arg)->end;
	int *fustrum = ((t_fustrum_thread*)arg)->fustrum;
	t_doom *doom = ((t_fustrum_thread*)arg)->doom;
	p = doom->player;
	while (x < end)
	{
		double tmp = (x / (double)(W - 1)) * doom->cam.range + doom->cam.near_left;
		pos.x = tmp * (-p.anglesin) - (-doom->cam.near_z) * p.anglecos + p.where.x;
		pos.y = tmp * (-p.anglecos) - (-doom->cam.near_z) * p.anglesin + p.where.y;
		pos.z = p.where.z + EYE_LVL;
		//fix!! also check starting from player sector
		fustrum[x] = find_sector(doom, pos);
		x += 1;
	}
	return (1);
}

//In how many sectors the camera/near_z is positioned
void	find_start_sectors(t_doom *doom, t_item *queue, int *qtotal)
{
	int			x;
	int			fustrum[W];
	t_fustrum_thread	arr[doom->nb.processors];

	cs();
	x = -1;	
	while (++x < doom->nb.processors)
	{
		arr[x].x = W /(double)doom->nb.processors * x;
		arr[x].end = W /(double)doom->nb.processors * (x + 1);
		arr[x].fustrum = fustrum;
		arr[x].doom = doom;
		tpool_add(&doom->tpool, fustrum_in_sector, &arr[x]);
		//fustrum_in_sector(&arr[x]);
	}
	tpool_wait(&doom->tpool);
	ce("Find screen x");
	cs();
	partition_screen(doom, fustrum, queue, qtotal);
	ce("partition screen x");
}
