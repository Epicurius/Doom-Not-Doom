/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 12:57:34 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/14 14:54:31 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom.h"

#define stackSize 100000

static enum
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

typedef struct s_flood_fill
{
	unsigned short	x1;
	unsigned short	x2;
	unsigned short	y;
	unsigned short	dir;
}				t_flood_fill;

t_flood_fill stack[stackSize];
int stackPointer;

inline int	Same(SDL_Surface *surface, Uint32 clr, int x, int y)
{
	if (((Uint32 *)surface->pixels)[y * surface->w + x] == clr)
		return (1);
	return (0);
}

int	pop4(unsigned short *x1, unsigned short *x2, unsigned short *y, unsigned short *dir)
{
	if (stackPointer)
	{
		stackPointer--;
		*x1 = stack[stackPointer].x1;
		*x2 = stack[stackPointer].x2;
		*y = stack[stackPointer].y;
		*dir = stack[stackPointer].dir;
		return (1);
	}
	return (0);
}

int	push4(unsigned short x1, unsigned short x2, unsigned short y, unsigned short dir)
{
	if (stackPointer < stackSize)
	{
		stack[stackPointer].x1 = x1;
		stack[stackPointer].x2 = x2;
		stack[stackPointer].y = y;
		stack[stackPointer].dir = dir;
		stackPointer++;
		return (1);
	}
	return (0);
}



void	up_fill(SDL_Surface *surface, t_flood_fill env, Uint32 *oldcolor, Uint32 *fillcolor)
{
	int	i;
	int	x;
	int	y;
	
	i = env.y + 1;
	env.x1 = ft_max(env.x1, 0);
	env.x2 = ft_min(env.x2, surface->w);
	for (x = env.x1; x < env.x2; x++)
	{
		y = env.y;
		if (Same(surface, oldcolor, x, y))
		{
			((Uint32 *)surface->pixels)[y * surface->w + x] = fillcolor;
			for (--y; y > -1; y--)
			{
				if (!Same(surface, oldcolor, x, y))
					break ;
				((Uint32 *)surface->pixels)[y * surface->w + x] = fillcolor;
			}
		}
		if (y < i && y < env.y && x > 0)
			push4(y + 1, i, x - 1, LEFT);
		else if (y > i && x < surface->w)
			push4(i + 1, y, x, RIGHT);
		i = y;
	}
	if (i < env.y && x < surface->w)
		push4(i + 1, env.y + 1, x, RIGHT);
}

void	down_fill(SDL_Surface *surface, t_flood_fill env, Uint32 *oldcolor, Uint32 *fillcolor)
{
	int	i;
	int	x;
	int	y;
	
	i = env.y - 1;
	env.x1 = ft_max(env.x1, 0);
	env.x2 = ft_min(env.x2, surface->w);
	for (x = env.x1; x < env.x2; x++)
	{
		y = env.y;
		if (Same(surface, oldcolor, x, y))
		{
			((Uint32 *)surface->pixels)[y * surface->w + x] = fillcolor;
			for (++y; y < surface->h; y++)
			{
				if (!Same(surface, oldcolor, x, y))
					break;
				((Uint32 *)surface->pixels)[y * surface->w + x] = fillcolor;
			}
		}
		if (y < i && x < surface->w)
			push4(y - 1, i, x, RIGHT);
		else if (y > i && y > env.y && x > 0)
			push4(i - 1, y, x - 1, LEFT);
		i = y;
	}
	if (env.y < i && x < surface->w)
		push4(env.y, i, x, RIGHT);
}

void	left_fill(SDL_Surface *surface, t_flood_fill env, Uint32 *oldcolor, Uint32 *fillcolor)
{
	int	i;
	int	x;
	
	i = env.y + 1;
	env.x1 = ft_max(env.x1 - 1, 0);
	env.x2 = ft_min(env.x2, surface->h);
	while (env.x1++ < env.x2)
	{
		x = env.y;
		if (Same(surface, oldcolor, x, env.x1))
		{
			((Uint32 *)surface->pixels)[env.x1 * surface->w + x] = fillcolor;
			for (--x; x > -1; x--)
			{
				if (!Same(surface, oldcolor, x, env.x1))
					break;
				((Uint32 *)surface->pixels)[env.x1 * surface->w + x] = fillcolor;
			}
		}
		if (x < i && x < env.y && env.x1 > 0)
			push4(x + 1, i, env.x1 - 1, UP);
		else if (x > i && env.x1 < surface->h)
			push4(i + 1, x, env.x1, DOWN);
		i = x;
	}
	if (i < env.y && env.x1 < surface->h)
		push4(i + 1, env.y + 1, env.x1, DOWN);
}

void	right_fill(SDL_Surface *surface, t_flood_fill env, Uint32 *oldcolor, Uint32 *fillcolor)
{
	int	i;
	int	x;
	int	y;
	
	i = env.y - 1;
	env.x1 = ft_max(env.x1, 0);
	env.x2 = ft_min(env.x2, surface->h);
	for (y = env.x1; y < env.x2; y++)
	{
		x = env.y;
		if (Same(surface, oldcolor, x, y))
		{
			((Uint32 *)surface->pixels)[y * surface->w + x] = fillcolor;
			for (++x; x < surface->w; x++)
			{
				if (!Same(surface, oldcolor, x, y))
					break;
				((Uint32 *)surface->pixels)[y * surface->w + x] = fillcolor;
			}
		}
		if (x < i && y < surface->h)
			push4(x - 1, i, y, DOWN);
		else if (x > i && x > env.y && y > 0) 
			push4(i - 1, x, y - 1, UP);
		i = x;
	}
	if (env.y < i && y < surface->h)
		push4(env.y, i, y, DOWN);
}


void CrissCross(t_doom *doom, SDL_Surface *surface, Uint32 fillcolor, int x, int y)
{
	t_flood_fill	env;
	Uint32			oldcolor;
	
	oldcolor = ((Uint32 *)surface->pixels)[y * surface->w + x];
	if (oldcolor == fillcolor)
		return ;
	stackPointer = 0;
	env.x1 = x;
	while (x < surface->w && Same(surface, oldcolor, x, y))
		((Uint32 *)surface->pixels)[y * surface->w + x++] = fillcolor;
	env.x2 = x;
	while (env.x1 > -1 && Same(surface, oldcolor, env.x1, y))
		((Uint32 *)surface->pixels)[y * surface->w + env.x1--] = fillcolor;
	env.x1++;
	if (y > 0)
		push4(env.x1, env.x2, y - 1, UP);
	if (y < surface->h - 1)
		push4(env.x1, env.x2, y + 1, DOWN);
	while (pop4(&env.x1, &env.x2, &env.y, &env.dir))
	{
		if (env.dir == UP)
			up_fill(surface, env, oldcolor, fillcolor);
		else if (env.dir == DOWN)
			down_fill(surface, env, oldcolor, fillcolor);
		else if (env.dir == LEFT)
			left_fill(surface, env, oldcolor, fillcolor);
		else if (env.dir == RIGHT)
			right_fill(surface, env, oldcolor, fillcolor);
	}
}


//typedef struct	s_coords
//{
//	int x;
//	int y;
//}				t_coords;
//
//typedef struct s_xywh
//{
//	int	x;
//	int	y;
//	int	w;
//	int	h;
//}				t_xywh;
//t_xywh	new_xywh1(int x, int y, int w, int h)
//{
//	t_xywh	coords;
//
//	coords.x = x;
//	coords.y = y;
//	coords.w = w;
//	coords.h = h;
//	return (coords);
//}
//void	dummy(void *dum, size_t dom)
//{
//}
//Uint32  get_color(SDL_Surface *surface, int x, int y)
//{
//    Uint32 *pixels;
//
//	pixels = surface->pixels;
//	return (pixels[y * surface->w + x]);
//}
//void	push_list(t_list **lst, void *content, size_t content_size)
//{
//	t_list *new;
//
//	new = ft_lstnew(content, content_size);
//	if (lst)
//		ft_lstadd(lst,  new);
//	else
//		*lst = new;
////	printf("c2: %d %d\n", ((t_coords *)content)->x, ((t_coords *)content)->y);
////	printf("p2: %d %d\n", ((t_coords *)new->content)->x, ((t_coords *)new->content)->y);
////	printf("l: %d %d %zu\n", ((t_coords *)(*lst)->content)->x, ((t_coords *)(*lst)->content)->y, (*lst)->content_size);
//}
//
//void	*pop_list(t_list **lst)
//{
//	void	*content;
//	t_list *temp;
//
//	if (!(content = (void *)malloc(sizeof((*lst)->content_size))))
//		exit (0);
////	printf("pop: %d %d %zu\n", ((t_coords *)(*lst)->content)->x, ((t_coords *)(*lst)->content)->y, (*lst)->content_size);
//	content = ft_memcpy(content, (*lst)->content, (*lst)->content_size);
////	printf("%d %d\n", ((t_coords *)content)->x, ((t_coords *)content)->y);
//	temp = (*lst)->next;
//	ft_lstdelone(lst, &dummy);
//	*lst = temp;
//	return (content);
//}
//
//void	set_pixel1(SDL_Surface *surface, int x, int y, Uint32 color)
//{
//	Uint32	*pixels;
//
//	pixels = surface->pixels;
//	if (x >= 0 && x < surface->w
//		&& y >= 0 && y < surface->h)
//	{
//		pixels[y * surface->w + x] = color;
//	}
//}
//
//void	flood_fill(SDL_Surface *surface, Uint32 replaceColor, int x, int y)
//{
//	t_list	*pix;
//	t_xywh *content;
//	t_xywh coord;
//	int iter = 1;
//	int ix;
//	int iy;
//	int	spanAbove;
//	int spanBelow;
//	
//	Uint32 targetColor = ((Uint32 *)surface->pixels)[y * surface->w + x];
//	if (targetColor == replaceColor)
//		return;
//	coord = new_xywh1(x, y, 0, 0);
//	push_list(&pix, &coord, sizeof(t_coords));
//	while (iter != 0 && (content = pop_list(&pix)) != NULL)
//	{
//		iter--;
//		ix = ((t_xywh *)content)->x;
//		iy = ((t_xywh *)content)->y;
//		free(content);
//		while (ix > 0 && get_color(surface, ix - 1, iy) == targetColor)
//			ix--;
//		spanAbove = 0;
//		spanBelow = 0;
//		while(ix < surface->w && get_color(surface, ix, iy) == targetColor)
//		{
//			set_pixel1(surface, ix, iy, replaceColor);
//			if(spanAbove == 0 && iy > 0 && get_color(surface, ix, iy - 1) == targetColor)
//			{
//				coord = new_xywh1(ix, iy - 1, 0, 0);
//				push_list(&pix, &coord, sizeof(t_xywh));
//				iter++;
//	            spanAbove = 1;
//	        }
//			else if (spanAbove == 1 && iy > 0 && get_color(surface, ix, iy - 1) != targetColor)
//				spanAbove = 0;
//			if (spanBelow == 0 && iy < surface->h - 1 && get_color(surface, ix, iy + 1) == targetColor)
//			{
//				coord = new_xywh1(ix, iy + 1, 0, 0);
//				push_list(&pix, &coord, sizeof(t_xywh));
//				iter++;
//	            spanBelow = 1;
//	        }
//	        else if (spanBelow == 1 && iy < surface->h - 1 && get_color(surface, ix, iy + 1) != targetColor)
//	            spanBelow = 0;
//	        ix++;
//	    }
//	}
//}