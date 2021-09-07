/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:00 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/07 15:45:38 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Draw a line to surface with color from vertice 1 to vertice 2.
 *	Dont draw outside surface borders.
 *	Bresehamn's algorithm.
 */
void	draw_line(SDL_Surface *surf, Uint32 color, t_point v1, t_point v2)
{
	t_point	cath;
	t_point	overflow;

	cath.x = abs(v2.y - v1.y);
	cath.y = abs(v2.x - v1.x);
	overflow.y = cath.y - cath.x;
	while (v1.x != v2.x || v1.y != v2.y)
	{
		if (v1.x >= 0 && v1.x <= surf->w && v1.y >= 0 && v1.y <= surf->h)
			((Uint32 *)surf->pixels)[v1.y * surf->w + v1.x] = color;
		overflow.x = overflow.y * 2;
		if (overflow.x > -(cath.x))
		{
			overflow.y -= cath.x;
			v1.x += ft_sign(v2.x - v1.x);
		}
		else if (overflow.x < cath.x)
		{
			overflow.y += cath.y;
			v1.y += ft_sign(v2.y - v1.y);
		}
	}
}

inline void	myPixel(SDL_Surface *surf, int x, int y)
{
	if (x >= 0 && x <= surf->w && y >= 0 && y <= surf->h)
		((Uint32 *)surf->pixels)[y * surf->w + x] = 0xff00ff00;
}

void	draw_line2(SDL_Surface *surface, Uint32 color, t_point p1, t_point p2)
{
	bool	y_longer;
	int		increment_val;
	int		end_val;
	int		dec_inc;
	int		j;
	int		i;

	p2.y -= p1.y;
	p2.x -= p1.x;
	j = 0;
	i = 0;
	y_longer = abs(p2.y) > abs(p2.x);
	if (y_longer)
		ft_swap(&p2.y, &p2.x);
	end_val = p2.x;
	increment_val = 1;
	if (p2.x < 0)
	{
		increment_val = -1;
		p2.x = -p2.x;
	}
	dec_inc = 0;
	if (p2.x != 0)
		dec_inc = (p2.y << 16) / p2.x;
	if (y_longer)
	{
		while (i != end_val)
		{
			myPixel(surface, p1.x + (j >> 16), p1.y + i);	
			j += dec_inc;
			i += increment_val;
		}
		return ;
	}
	while (i != end_val)
	{
		myPixel(surface, p1.x + i, p1.y + (j >> 16));
		j += dec_inc;
		i += increment_val;
	}
}
