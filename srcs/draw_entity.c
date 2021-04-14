
#include "doom.h"

int	rotate_entity(t_doom *doom, t_entity *entity, t_entity_render *render)
{
	t_xyz dist;
	t_xyz screen;

	dist.x = entity->where.x - doom->player.where.x;
	dist.y = entity->where.z - doom->player.where.z - EYE_LVL;
	dist.z = entity->where.y - doom->player.where.y;
	screen.x = dist.x * doom->player.anglesin
			- dist.z * doom->player.anglecos;
	screen.z = dist.x * doom->player.anglecos
			+ dist.z * doom->player.anglesin;
	screen.y = dist.y + screen.z * doom->player.pitch;
	if (screen.z <= 1) //or outside screen borders?
		return (0);
	render->screen = screen;
	render->surface = doom->surface;
	render->scale = doom->entity_stats[entity->type].scale;
	render->texture = doom->sprites[entity->type].surface;
	render->bxpm = &doom->sprites[entity->type].bxpm;
	render->img = doom->sprites[entity->type].pos[entity->state][entity->frame][entity->angle];
	return (1);
}


void	find_visible_entitys(t_doom *doom, t_entity_render *render, int *nb)
{
	int s;
	int i;
	t_xyz pos;

	s = -1;
	while (++s < doom->nb.sectors)
	{
		if (!doom->sectors[s].visible)
			continue ;
		i = -1;
		while (++i < doom->nb.entities)
		{
			if (!doom->entity[i].render)
				continue ;
			if (doom->entity[i].sector != doom->sectors[s].id)
				continue ;
			if (!rotate_entity(doom, &doom->entity[i], &render[*nb]))
				continue ;
			*nb += 1;
		}
	}
}

void	 project_entity(t_doom *doom, t_entity_render *render)
{
	render->screen.x = doom->w2 + (render->screen.x * doom->cam.scale / -render->screen.z);
	render->screen.y = doom->h2 + (render->screen.y * doom->cam.scale / -render->screen.z);
	render->size.x	= render->img.w * render->scale / render->screen.z;
	render->size.y	= render->img.h * render->scale / render->screen.z;
	render->start.x	= render->screen.x - render->size.x / 2;
	render->end.x	= render->screen.x + render->size.x / 2;
	render->start.y = render->screen.y - render->size.y;
	render->end.y	= render->screen.y;
	render->clamp_start.x	= ft_clamp(render->start.x, 0, W - 1);
	render->clamp_end.x	= ft_clamp(render->end.x,   0, W - 1);
	render->clamp_start.y	= ft_clamp(render->start.y, 0, H - 1);
	render->clamp_end.y	= ft_clamp(render->end.y,   0, H - 1);
	render->xrange = render->end.x - render->start.x;
	render->yrange = render->end.y - render->start.y;
}

void 	DrawEntity(t_doom *doom)
{
	int		i;
	int		nb;
	t_entity_render e[doom->nb.entities];

	nb = 0;
	find_visible_entitys(doom, e, &nb);
	//render in order of z!!!!
	i = -1;
	while (++i < nb)
		project_entity(doom, &e[i]);
	i = -1;
	while (++i < nb)
		blit_entity(&e[i]);
}
