
#include "doom.h"

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
		double tmp = (x / (double)(doom->surface->w - 1)) * doom->cam.range + doom->cam.near_left;
		pos.x = tmp * (-p.anglesin) - (-doom->cam.near_z) * p.anglecos + p.where.x;
		pos.y = tmp * p.anglecos - (-doom->cam.near_z) * p.anglesin + p.where.y;
		//pos.z = p.where.z + EYE_LVL;
		//fix!! also check starting from player sector
		fustrum[x] = find_sector(doom, pos);
		x += 1;
	}
	return (1);
}

//In how many sectors the camera/near_z is positioned
int		find_start_sectors(t_doom *doom)
{
	int					x;
	int					w;
	t_fustrum_thread	arr[doom->nb.processors];

	x = -1;
	w = doom->surface->w;	
	while (++x < doom->nb.processors)
	{
		arr[x].x = w /(double)doom->nb.processors * x;
		arr[x].end = min(w /(double)doom->nb.processors * (x + 1), w);
		arr[x].fustrum = doom->fustrum;
		arr[x].doom = doom;
		tpool_add(&doom->tpool, fustrum_in_sector, &arr[x]);
	}
	tpool_wait(&doom->tpool);
	return (1);
}
