/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/08/04 12:16:08 nneronin
 * Updated: 2021/09/05 07:08:14 nneronin
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
