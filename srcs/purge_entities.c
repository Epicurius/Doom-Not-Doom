/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Function to remove all spawnable entities.
 *	Mainly a debug/developer function.
 */
void	purge_entities(t_doom *doom)
{
	t_list		*curr;

	curr = doom->entity;
	while (curr != NULL)
	{
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
