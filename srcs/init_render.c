
#include "doom.h"

void	init_render(t_doom *doom)
{
	int x;

	if (!(doom->fustrum = ft_memalloc(sizeof(int) * W)))
		return ;
	if (!(doom->render = ft_memalloc(sizeof(t_render) * W)))
		return ;
	if (!(doom->zbuffer = ft_memalloc(sizeof(double) * (W * H))))
		return ;
	doom->surface->userdata = doom->zbuffer;
	x = -1;
	while (++x < W)
	{
		doom->render[x].surface = doom->surface;
		doom->render[x].sectors = doom->sectors;
		doom->render[x].fustrum = doom->fustrum;
		doom->render[x].skybox	= doom->skybox;
		doom->render[x].mtx		= doom->mtx;
		doom->render[x].stx		= doom->stx;
	}
}
