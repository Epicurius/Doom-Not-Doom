
#include "doom.h"

typedef struct	s_entity_render
{
	SDL_Surface *surface;
	t_texture *texture;
	t_xyz	screen;
	double	scale;
	double	ratio;
	t_v2	size;
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	xstart;
	int	ystart;
	int	xend;
	int	yend;
	double	xrange;
	double	yrange;
}		t_entity_render;

int rotate_entity(t_doom *doom, t_entity *e, t_entity_render *render)
{
	t_xyz dist;
	t_xyz screen;
	t_player player;

	player = doom->player;
	dist.x = e->where.x - player.where.x;
	dist.y = e->where.z - player.where.z;
	dist.z = e->where.y - player.where.y;
	screen.x = dist.x * player.anglesin - dist.z * player.anglecos;
	screen.z = dist.x * player.anglecos + dist.z * player.anglesin;
	screen.y = dist.y + screen.z * doom->player.pitch;
	if (screen.z <= 1) //or outside screen borders?
		return (0);
	render->screen = screen;
	render->surface = doom->surface;
	render->texture = &doom->entity_t[e->tx];
	render->scale = e->scale;
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
			if (doom->entity[i].sect != doom->sectors[s].id)
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
	render->ratio = render->texture->w / (double)render->texture->h;
	render->size.x = W * render->scale / render->screen.z; //10 size
	render->size.y = render->size.x * render->ratio;
	render->x1 = render->screen.x - render->size.y / 4;
	render->x2 = render->screen.x + render->size.y / 4;
	render->y1 = render->screen.y - render->size.x / 2;
	render->y2 = render->screen.y;
	render->xstart = ft_clamp(render->x1, 0, W - 1);
	render->xend = ft_clamp(render->x2, 0, W - 1);
	render->ystart = ft_clamp(render->y1, 0, H - 1);
	render->yend  = ft_clamp(render->y2, 0, H - 1);
	render->xrange = render->x2 - render->x1;
	render->yrange = render->y2 - render->y1;
}

void	put_entity_pixel(t_entity_render *render, int coord, t_v2 text)
{
	Uint32		pixel;

	if (((double*)render->surface->userdata)[coord] < render->screen.z)
		return ;
	pixel = ((Uint32*)render->texture->surface->pixels)
		[(int)text.y * render->texture->w + (int)text.x];
	if (((pixel >> 24) & 0xFF) < OPAQUE)
		return ;
	((Uint32*)render->surface->pixels)[coord] = pixel;
	((double*)render->surface->userdata)[coord] = render->screen.z;
}

void	render_entity(t_entity_render *render)
{
	t_v2 alpha;
	t_v2 text;
	t_texture *t;

	t = render->texture;
	int y = render->ystart;
	while (++y < render->yend)
	{
		alpha.y = (y - render->y1) / render->yrange;
		text.y = (1.0 - alpha.y) * t->y + alpha.y * t->h;
		int x = render->xstart;
		while (++x < render->xend)
		{
			alpha.x = (x - render->x1) / render->xrange;
			text.x = (1.0 - alpha.x) * t->x + alpha.x * t->w;
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

	i = -1;
	while (++i < nb)
		project_entity(doom, &e[i]);
	i = -1;
	while (++i < nb)
		render_entity(&e[i]);
}
