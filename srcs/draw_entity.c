
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
	if (screen.z <= 0.5)
		return (0);
	render->screen = xyz(screen.x, screen.y, screen.z);
	render->scale = doom->entity_stats[entity->type].scale;
	render->pos = doom->sheet[entity->type].pos[entity->state][entity->frame][entity->angle];
	return (1);
}

void	entity_threads(t_doom *doom, t_entity_render render, t_entity *entity, t_entity_render *thread)
{
	int y;

	y = -1;
	int i = render.clamp_end.y - render.clamp_start.y;
	while (++y < 10)
	{
		ft_memcpy((void*)&thread[y], (void*)&render, sizeof(t_entity_render));
		thread[y].clamp_start.y	+= i / 10.0 * y;
		thread[y].clamp_end.y	+= i / 10.0 * (y + 1);
		thread[y].clamp_end.y	= min(thread[y].clamp_end.y, render.clamp_end.y);
		thread[y].surface = doom->surface;
		thread[y].bxpm = &doom->sheet[entity->type].bxpm;
		thread[y].shooting = doom->player.shooting;
		thread[y].dmg = 10;
		thread[y].hp = &entity->hp;
		tpool_add(&doom->tpool, blit_entity, &thread[y]);
	}
}

void	DrawEntity(t_doom *doom)
{
	int s;
	t_list *curr;
	t_entity *entity;
	t_entity_render render;
	t_entity_render	thread[10];

	s = -1;
	while (++s < doom->nb.sectors)
	{
		if (!doom->sectors[s].visible)
			continue ;
		curr = doom->entity;
		while (curr)
		{
			entity = curr->content;
			curr = curr->next;
			if (entity->render && entity->sector == doom->sectors[s].id)
			{
				rotate_entity(doom, entity, &render);
				project_entity(doom, &render);
				tpool_wait(&doom->tpool);
				entity_threads(doom, render, entity, thread);
			}
		}
	}
	tpool_wait(&doom->tpool);
}
