/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:36:35 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/22 16:40:52 by nneronin         ###   ########.fr       */
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
