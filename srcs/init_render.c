
#include "doom.h"

void	init_render(t_doom *doom)
{
	int x;

	x = -1;
	if (!(doom->fustrum = ft_memalloc(sizeof(int) * doom->surface->w)))
		return ;
	if (!(doom->render = ft_memalloc(sizeof(t_render) * doom->nb.threads)))
		return ;
	if (!(doom->zbuffer = ft_memalloc(sizeof(double) * (doom->surface->w * doom->surface->h))))
		return ;
	doom->surface->userdata = doom->zbuffer;
	while (++x < doom->nb.threads)
	{
		doom->render[x].surface = doom->surface;
		doom->render[x].sectors = doom->sectors;
		doom->render[x].fustrum = doom->fustrum;
		doom->render[x].skybox	= doom->skybox;
		doom->render[x].mtx		= doom->mtx;
		doom->render[x].stx		= doom->stx;
	}
}
