/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:36:35 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/16 09:20:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	get_entity_state_name(t_entity *entity)
{
	if (entity->state == DEATH)
		ft_printf("DEATH\n");
	else if (entity->state == ATTACK)
		ft_printf("ATTACK\n");
	else if (entity->state == MOVE)
		ft_printf("MOVE\n");
	else if (entity->state == IDLE)
		ft_printf("IDLE\n");
}


void	what_vert(t_doom *doom)
{
	int i = -1;
	t_sector *sect = &doom->sectors[doom->player.sector];
	while (++i < sect->npoints)
	{
		if (965 > sect->wall[i]->cx1 && 955 < sect->wall[i]->cx1)
			printf("%.2f %.2f\n", sect->wall[i]->v1.x, sect->wall[i]->v1.y);
	}
}

