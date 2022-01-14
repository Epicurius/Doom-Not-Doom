/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/08 10:51:39 nneronin
 * Updated: 2021/12/14 13:40:23 nneronin
 */

#include "doom.h"

void	init_render(t_doom *doom)
{
	int	i;

	i = -1;
	doom->sectbool = protalloc(sizeof(char) * doom->nb.sectors);
	doom->render = protalloc(sizeof(t_render) * doom->nb.threads);
	doom->zbuffer = protalloc(sizeof(float)
			* (doom->surface->w * doom->surface->h));
	doom->surface->userdata = doom->zbuffer;
	while (++i < doom->nb.threads)
	{
		doom->render[i].surface = doom->surface;
		doom->render[i].sectors = doom->sectors;
		doom->render[i].nb_sectors = doom->nb.sectors;
		doom->render[i].skybox = doom->skybox;
		doom->render[i].mtx = doom->mtx;
		doom->render[i].stx = doom->stx;
		doom->render[i].center = doom->c;
		doom->render[i].player = &doom->player;
		doom->render[i].cam = &doom->cam;
	}
}
