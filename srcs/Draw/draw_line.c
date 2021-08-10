/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:00 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/10 16:24:35 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
