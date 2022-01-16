/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_vec4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:54 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:24:54 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	vec4i_swap(t_vec4i *v1, t_vec4i *v2)
{
	t_vec4i	temp;
	int		i;

	temp = *v1;
	i = -1;
	while (++i < VEC4_SIZE)
		v1->v[i] = v2->v[i];
	i = -1;
	while (++i < VEC4_SIZE)
		v2->v[i] = temp.v[i];
}

void	vec4_swap(t_vec4 *v1, t_vec4 *v2)
{
	t_vec4	temp;
	int		i;

	temp = *v1;
	i = -1;
	while (++i < VEC4_SIZE)
		v1->v[i] = v2->v[i];
	i = -1;
	while (++i < VEC4_SIZE)
		v2->v[i] = temp.v[i];
}

t_vec4i	vec4_to_vec4i(t_vec4 src)
{
	return (vec4i(src.x, src.y, src.w, src.h));
}
