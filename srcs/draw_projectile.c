
#include "doom.h"

t_sprite_render project_projectile(t_doom *doom, t_projectile *orb)
{
	t_xyz dist;
	t_sprite_render render;

	dist.x = orb->where.x - doom->player.where.x;
	dist.y = orb->where.z - doom->player.where.z - EYE_LVL;
	dist.z = orb->where.y - doom->player.where.y;
	render.screen.x = dist.x * doom->player.anglesin - dist.z * doom->player.anglecos;
	render.screen.z = dist.x * doom->player.anglecos + dist.z * doom->player.anglesin;
	render.screen.y = dist.y + render.screen.z * doom->player.pitch;
	if (render.screen.z <= 1) //or outside screen borders?
		return (render);
	render.surface = doom->surface;
	render.bxpm = &doom->sheet[0].bxpm;
	render.pos = doom->sheet[0].pos[0][0][4];
	render.screen.y = doom->h2 + (render.screen.y * doom->cam.scale / -render.screen.z);
	render.screen.x = doom->w2 + (render.screen.x * doom->cam.scale / -render.screen.z);
	render.size.x = render.pos.w * 20 / render.screen.z;
	render.size.y = render.pos.h * 20 / render.screen.z;
	render.start.x = render.screen.x - render.size.x / 2;
	render.end.x   = render.screen.x + render.size.x / 2;
	render.start.y = render.screen.y - render.size.y;
	render.end.y   = render.screen.y;
	render.clamp_start.x = ft_clamp(render.start.x, 0, W - 1);
	render.clamp_end.x = ft_clamp(render.end.x, 0, W - 1);
	render.clamp_start.y = ft_clamp(render.start.y, 0, H - 1);
	render.clamp_end.y  = ft_clamp(render.end.y, 0, H - 1);
	render.xrange = render.end.x - render.start.x;
	render.yrange = render.end.y - render.start.y;
	return (render);
}

void 	DrawProjectiles(t_doom *doom)
{
	int i;
	t_sprite_render render;

	i = -1;
	while (++i < doom->nb.projectiles)
	{
		if (!doom->orb[i].render || !doom->sectors[doom->orb[i].sector].visible)
			continue ;
		render = project_projectile(doom, &doom->orb[i]);
		if (render.screen.z <= 1)
			continue ;
		blit_sprite(&render);
	}
}
