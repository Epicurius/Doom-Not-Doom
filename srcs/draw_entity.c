
#include "doom.h"

typedef struct		s_entity_render
{
	SDL_Surface	*surface;
	t_texture	*texture;
	SDL_Surface	*surf;
	t_xyz		screen;
	double		scale_w;
	double		scale_h;
	t_xyz		start;
	t_xyz		end;
	t_xyz		clamp_start;
	t_xyz		clamp_end;
	double		xrange;
	double		yrange;
	t_rect		img;
}			t_entity_render;

int rotate_entity(t_doom *doom, t_entity *entity, t_entity_render *render)
{
	t_xyz dist;
	t_xyz screen;
	t_player player;

	player = doom->player;
	dist.x = entity->where.x - player.where.x;
	dist.y = entity->where.z - player.where.z;
	dist.z = entity->where.y - player.where.y;
	screen.x = dist.x * player.anglesin - dist.z * player.anglecos;
	screen.z = dist.x * player.anglecos + dist.z * player.anglesin;
	screen.y = dist.y + screen.z * doom->player.pitch;
	if (screen.z <= 1) //or outside screen borders?
		return (0);
	render->screen = screen;
	render->surface = doom->surface;
	render->scale_w = entity->scale;
	render->surf = doom->sprites[entity->type].surface;
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
			if (*nb >= MAX_ENTITIES_RENDERED - 1)
				return ;
			*nb += 1;
		}
	}
}

void	 project_entity(t_doom *doom, t_entity_render *render)
{
	render->screen.y = doom->h2 + (render->screen.y * doom->cam.scale / -render->screen.z);
	render->screen.x = doom->w2 + (render->screen.x * doom->cam.scale / -render->screen.z);
	render->scale_w = W * render->scale_w / render->screen.z;
	render->scale_h = render->scale_w * render->img.ratio;
	render->start.x = render->screen.x - render->scale_h;
	render->end.x	= render->screen.x + render->scale_h;
	render->start.y = render->screen.y - render->scale_w * 2;
	render->end.y	= render->screen.y;;
	render->clamp_start.x = ft_clamp(render->start.x, 0, W - 1);
	render->clamp_end.x = ft_clamp(render->end.x, 0, W - 1);
	render->clamp_start.y = ft_clamp(render->start.y, 0, H - 1);
	render->clamp_end.y  = ft_clamp(render->end.y, 0, H - 1);
	render->xrange = render->end.x - render->start.x;
	render->yrange = render->end.y - render->start.y;
}

void	put_entity_pixel(t_entity_render *render, int coord, t_xyz text)
{
	Uint32		pixel;

	if (((double*)render->surface->userdata)[coord] < text.z)
		return ;
	pixel = ((Uint32*)render->surf->pixels)
		[(int)text.y * render->surf->w + (int)text.x];
	if (pixel == 0xFF800080)
		return ;
	((Uint32*)render->surface->pixels)[coord] = pixel;
	((double*)render->surface->userdata)[coord] = text.z;
}

void	render_entity(t_entity_render *render)
{
	t_v2 alpha;
	t_xyz text;

	text.z = render->screen.z;
	int y = render->clamp_start.y;
	while (++y < render->clamp_end.y)
	{
		alpha.y = (y - render->start.y) / render->yrange;
		text.y = (1.0 - alpha.y) * render->img.y1 + alpha.y * render->img.y2;
		int x = render->clamp_start.x;
		while (++x < render->clamp_end.x)
		{
			alpha.x = (x - render->start.x) / render->xrange;
			text.x = (1.0 - alpha.x) * render->img.x1 + alpha.x * render->img.x2;
			put_entity_pixel(render, y * W + x, text);
		}
	}
}

void 	DrawEntity(t_doom *doom)
{
	int		i;
	int		nb;
	t_entity_render e[MAX_ENTITIES_RENDERED];

	nb = 0;
	find_visible_entitys(doom, e, &nb);
	//render in order of z!!!!
	i = -1;
	while (++i < nb)
		project_entity(doom, &e[i]);
	i = -1;
	while (++i < nb)
		render_entity(&e[i]);
}
