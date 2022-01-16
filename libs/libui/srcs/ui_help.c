/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:22:54 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:22:55 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	point_in_rect(t_vec2i point, t_vec4i rect)
{
	if (point.x >= rect.x
		&& point.y >= rect.y
		&& point.x < rect.x + rect.w
		&& point.y < rect.y + rect.h)
		return (1);
	return (0);
}

int	rect_in_rect(t_vec4i rect1, t_vec4i rect2)
{
	if (rect1.x < rect2.x + rect2.w
		&& rect1.x + rect1.w > rect2.x
		&& rect1.y < rect2.y + rect2.h
		&& rect1.h + rect1.y > rect2.y)
		return (1);
	return (0);
}

void	pointer_swap(void *p1, void *p2)
{
	void	*temp;

	temp = p1;
	p1 = p2;
	p2 = temp;
}

int	dist(t_vec2i p1, t_vec2i p2)
{
	return (sqrt((p2.x - p1.x) * (p2.x - p1.x)
			+ (p2.y - p1.y) * (p2.y - p1.y)));
}

float	fdist(t_vec2 p1, t_vec2 p2)
{
	return (sqrt((p2.x - p1.x) * (p2.x - p1.x)
			+ (p2.y - p1.y) * (p2.y - p1.y)));
}
