
#include "doom.h"

void	 project_entity(t_doom *doom, t_entity_render *render)
{
	render->screen.x = doom->w2 + (render->screen.x * doom->cam.scale / -render->screen.z);
	render->screen.y = doom->h2 + (render->screen.y * doom->cam.scale / -render->screen.z);
	render->size.x	= render->pos.w * render->scale / render->screen.z;
	render->size.y	= render->pos.h * render->scale / render->screen.z;
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

int	rotate_entity(t_doom *doom, t_entity *entity, t_entity_render render, t_entity_render *thread)
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
	if (screen.z <= 0.5)
		return (0);
	render.screen = xyz(screen.x, screen.y, screen.z);
	render.scale = doom->entity_stats[entity->type].scale;
	render.pos = doom->sprites[entity->type].pos[entity->state][entity->frame][entity->angle];
	project_entity(doom, &render);
	tpool_wait(&doom->tpool);
	blit_entity(doom, render, entity->type, thread);
	return (1);
}


void	find_visible_entitys(t_doom *doom)
{
	int s;
	int i;
	t_entity_render render;
	t_entity_render	thread[10];

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
			rotate_entity(doom, &doom->entity[i], render, thread);
		}
	}
	tpool_wait(&doom->tpool);
}

void 	DrawEntity(t_doom *doom)
{
	int		i;
	int		nb;

	nb = 0;
	find_visible_entitys(doom);
	//i = -1;
	//while (++i < nb)
}
