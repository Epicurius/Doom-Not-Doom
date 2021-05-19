/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zbuffer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:54:09 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/19 14:55:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	set_zbuffer_pixel_color(t_doom *doom, int i, double max_z)
{
	double	alpha;

	alpha = 1 - doom->zbuffer[i] / max_z;
	if (doom->zbuffer[i] >= 0 && alpha >= 0 && alpha <= 1)
		((Uint32*)doom->surface->pixels)[i] = (int)(alpha * 0xFF) << 24
							| (int)(alpha * 0xFF) << 16
							| (int)(alpha * 0xFF) << 8
							| (int)(alpha * 0xFF);
	else
		((Uint32*)doom->surface->pixels)[i] = 0;
}

/*
**	Give every pixel a shade according to the zbuffer
*/
void	shade_zbuffer(t_doom *doom)
{
	double	max_z;
	int	i;

	max_z = 30;
	i = -1;
	while (++i < W * H)
		set_zbuffer_pixel_color(doom, i, max_z);
	i = -1;
	printf("%f\n", doom->zbuffer[360 * W + 640]);
}
