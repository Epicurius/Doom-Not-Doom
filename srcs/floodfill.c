/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 12:57:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/24 15:52:19 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

#define FF_STACK_SIZE 25000

enum
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

typedef struct s_ff_pos
{
	short	x1;
	short	x2;
	short	y;
	short	dir;
}					t_ff_pos;

typedef struct s_flood_fill
{
	t_ff_pos	pos;
	Uint32		oldcolor;
	int			stackPointer;
	t_ff_pos	stack[FF_STACK_SIZE];
}				t_flood_fill;

static inline int	clr_compare(SDL_Surface *surface, Uint32 clr, int x, int y)
{
	if (((Uint32 *)surface->pixels)[y * surface->w + x] == clr)
		return (1);
	return (0);
}

static inline int	pop4(t_flood_fill *env)
{
	if (env->stackPointer)
	{
		env->stackPointer--;
		env->pos = env->stack[env->stackPointer];
		return (1);
	}
	return (0);
}

static inline int	push4(t_flood_fill *env, t_ff_pos pos)
{
	if (env->stackPointer < FF_STACK_SIZE)
	{
		env->stack[env->stackPointer] = pos;
		env->stackPointer++;
		return (1);
	}
	return (0);
}

static void	up_fill(SDL_Surface *surface, t_flood_fill *env, Uint32 newcolor)
{
	int	i;
	int	x;
	int	y;

	i = env->pos.y + 1;
	env->pos.x1 = ft_max(env->pos.x1, 0);
	env->pos.x2 = ft_min(env->pos.x2, surface->w);
	x = env->pos.x1 - 1;
	while (++x < env->pos.x2)
	{
		y = env->pos.y;
		if (clr_compare(surface, env->oldcolor, x, y))
		{
			((Uint32 *)surface->pixels)[y *surface->w + x] = newcolor;
			while (--y > -1 && clr_compare(surface, env->oldcolor, x, y))
				((Uint32 *)surface->pixels)[y *surface->w + x] = newcolor;
			if (y < i - 1 && x > 0)
				push4(env, (t_ff_pos){y + 1, i, x - 1, LEFT});
			else if (y > i + 1 && x < surface->w)
				push4(env, (t_ff_pos){i + 1, y, x, RIGHT});
		}
		else if (y > i + 1 && x < surface->w)
			push4(env, (t_ff_pos){i + 1, y, x, RIGHT});
		i = y;
	}
	if (i < env->pos.y && x < surface->w)
		push4(env, (t_ff_pos){i + 1, env->pos.y + 1, x, RIGHT});
}

static void	down_fill(SDL_Surface *surface, t_flood_fill *env, Uint32 newcolor)
{
	int	i;
	int	x;
	int	y;

	i = env->pos.y - 1;
	env->pos.x1 = ft_max(env->pos.x1, 0);
	env->pos.x2 = ft_min(env->pos.x2, surface->w);
	x = env->pos.x1 - 1;
	while (++x < env->pos.x2)
	{
		y = env->pos.y;
		if (clr_compare(surface, env->oldcolor, x, y))
		{
			((Uint32 *)surface->pixels)[y *surface->w + x] = newcolor;
			while (++y < surface->h && clr_compare(surface, env->oldcolor, x, y))
				((Uint32 *)surface->pixels)[y *surface->w + x] = newcolor;
			if (y < i - 1 && x < surface->w)
				push4(env, (t_ff_pos){y - 1, i, x, RIGHT});
			else if (y > i + 1 && x > 0)
				push4(env, (t_ff_pos){i + 1, y, x - 1, LEFT});
		}
		else if (y < i && x < surface->w)
			push4(env, (t_ff_pos){y - 1, i, x, RIGHT});
		i = y;
	}
	if (env->pos.y < i && x < surface->w)
		push4(env, (t_ff_pos){env->pos.y, i, x, RIGHT});
}

static void	left_fill(SDL_Surface *surface, t_flood_fill *env, Uint32 newcolor)
{
	int	i;
	int	x;
	int	y;

	i = env->pos.y + 1;
	env->pos.x1 = ft_max(env->pos.x1, 0);
	env->pos.x2 = ft_min(env->pos.x2, surface->h);
	y = env->pos.x1 - 1;
	while (++y < env->pos.x2)
	{
		x = env->pos.y;
		if (clr_compare(surface, env->oldcolor, x, y))
		{
			((Uint32 *)surface->pixels)[y *surface->w + x] = newcolor;
			while (--x > -1 && clr_compare(surface, env->oldcolor, x, y))
				((Uint32 *)surface->pixels)[y * surface->w + x] = newcolor;
			if (x < i - 1 && y > 0)
				push4(env, (t_ff_pos){x + 1, i, y - 1, UP});
			else if (x > i + 1 && y < surface->h)
				push4(env, (t_ff_pos){i + 1, x, y, DOWN});
		}
		else if (x > i + 1 && y < surface->h)
			push4(env, (t_ff_pos){i + 1, x, y, DOWN});
		i = x;
	}
	if (i < env->pos.y && y < surface->h)
		push4(env, (t_ff_pos){i + 1, env->pos.y + 1, y, DOWN});
}

static void	right_fill(SDL_Surface *surface, t_flood_fill *env, Uint32 newcolor)
{
	int	i;
	int	x;
	int	y;

	i = env->pos.y - 1;
	env->pos.x1 = ft_max(env->pos.x1, 0);
	env->pos.x2 = ft_min(env->pos.x2, surface->h);
	y = env->pos.x1 - 1;
	while (++y < env->pos.x2)
	{
		x = env->pos.y;
		if (clr_compare(surface, env->oldcolor, x, y))
		{
			((Uint32 *)surface->pixels)[y *surface->w + x] = newcolor;
			while (++x < surface->w && clr_compare(surface, env->oldcolor, x, y))
				((Uint32 *)surface->pixels)[y * surface->w + x] = newcolor;
			if (x < i - 1 && y < surface->h)
				push4(env, (t_ff_pos){x - 1, i, y, DOWN});
			else if (x > i + 1 && y > 0)
				push4(env, (t_ff_pos){i + 1, x, y - 1, UP});
		}
		else if (x < i - 1 && y < surface->h)
			push4(env, (t_ff_pos){x - 1, i, y, DOWN});
		i = x;
	}
	if (env->pos.y < i && y < surface->h)
		push4(env, (t_ff_pos){env->pos.y, i, y, DOWN});
}

void	flood_fill2(SDL_Surface *surface, t_flood_fill *env, Uint32 newcolor)
{
	while (pop4(env))
	{
		if (env->pos.dir == UP)
			up_fill(surface, env, newcolor);
		else if (env->pos.dir == DOWN)
			down_fill(surface, env, newcolor);
		else if (env->pos.dir == LEFT)
			left_fill(surface, env, newcolor);
		else
			right_fill(surface, env, newcolor);
	}	
}

void	flood_fill(SDL_Surface *surface, Uint32 newcolor, int x, int y)
{
	t_flood_fill	env;

	env.oldcolor = ((Uint32 *)surface->pixels)[y * surface->w + x];
	if (env.oldcolor == newcolor)
		return ;
	env.stackPointer = 0;
	((Uint32 *)surface->pixels)[y * surface->w + x] = newcolor;
	env.pos.x1 = x;
	while (++x < surface->w && clr_compare(surface, env.oldcolor, x, y))
		((Uint32 *)surface->pixels)[y * surface->w + x] = newcolor;
	env.pos.x2 = x - 1;
	while (--env.pos.x1 > -1 && clr_compare(surface, env.oldcolor, env.pos.x1, y))
		((Uint32 *)surface->pixels)[y * surface->w + env.pos.x1] = newcolor;
	env.pos.x1++;
	if (y > 0)
		push4(&env, (t_ff_pos){env.pos.x1, env.pos.x2, y - 1, UP});//2
	if (y < surface->h - 1)
		push4(&env, (t_ff_pos){env.pos.x1, env.pos.x2, y + 1, DOWN});//3
	flood_fill2(surface, &env, newcolor);
}

