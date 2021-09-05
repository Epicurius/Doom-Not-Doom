/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purge_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 12:16:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/05 07:08:14 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Function to remove all spawnable entities.
 *	Mainly a debug/developer function.
 */
void	purge_entities(t_doom *doom)
{
	t_list		*curr;
	t_entity	*entity;

	curr = doom->entity;
	while (curr != NULL)
	{
		entity = curr->content;
		if (((t_entity *)curr->content)->type == ALFRED
			|| ((t_entity *)curr->content)->type == SPOOKY
			|| ((t_entity *)curr->content)->type == GHOST
			|| ((t_entity *)curr->content)->type == MED_KIT
			|| ((t_entity *)curr->content)->type == RIFT)
			curr = ft_dellstnode(&doom->entity, curr);
		else
			curr = curr->next;
	}
}
