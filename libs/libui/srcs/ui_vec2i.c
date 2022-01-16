/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_vec2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:52 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:24:52 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	vec2i_swap(t_vec2i *v1, t_vec2i *v2)
{
	t_vec2i	temp;
	int		i;

	temp = *v1;
	i = -1;
	while (++i < VEC2_SIZE)
		v1->v[i] = v2->v[i];
	i = -1;
	while (++i < VEC2_SIZE)
		v2->v[i] = temp.v[i];
}

void	vec2_swap(t_vec2 *v1, t_vec2 *v2)
{
	t_vec2	temp;
	int		i;

	temp = *v1;
	i = -1;
	while (++i < VEC2_SIZE)
		v1->v[i] = v2->v[i];
	i = -1;
	while (++i < VEC2_SIZE)
		v2->v[i] = temp.v[i];
}

t_vec2i	vec2i_add(t_vec2i v1, t_vec2i v2)
{
	t_vec2i	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	return (v);
}

t_vec2i	vec2i_sub(t_vec2i v1, t_vec2i v2)
{
	t_vec2i	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	return (v);
}
