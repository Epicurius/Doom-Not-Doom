/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:00 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/07 14:07:14 by nneronin         ###   ########.fr       */
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

void	myPixel(SDL_Surface *surf, int x, int y)
{
	if (x >= 0 && x <= surf->w && y >= 0 && y <= surf->h)
		((Uint32 *)surf->pixels)[y * surf->w + x] = 0xff00ff00;
}
//EFLA
void efla(SDL_Surface *surf, Uint32 color, t_point v1, t_point v2)
{
	bool yLonger = false;
	int incrementVal;
	double divDiff;
	int shortLen = v2.y - v1.y;
	int longLen = v2.x - v1.x;
	
	if (abs(shortLen) > abs(longLen))
	{
		ft_swap(shortLen, longLen);
		yLonger=true;
	}

	if (longLen < 0)
		incrementVal = -1;
	else
		incrementVal = 1;
	if (shortLen == 0)
		divDiff = longLen;
	else
		divDiff = (double)longLen / (double)shortLen;
		
	if (yLonger)
	{
		for (int i = 0; i != longLen; i += incrementVal)
		{
			myPixel(surf, v1.x + (int)((double)i/divDiff),v1.y + i);
		}
	}
	else
	{
		for (int i = 0; i != longLen; i += incrementVal)
		{
			myPixel(surf, v1.x+i,v1.y+(int)((double)i/divDiff));
		}
	}
	//draw_line1(surf, color, v1, v2);
}
