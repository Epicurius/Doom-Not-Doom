/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:56:55 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/13 15:47:56 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int correct_sector_index(t_doom *doom, int id)
{
	int	i;
	
	i = -1;
	while  (++i < doom->nb.sectors)
		if (doom->sectors[i].id == id)
			break ;
	if (i < doom->nb.sectors)
		return (i);
	error_msg("Could not find correct sector.");
	exit (1);
}

void	fix_sector_index(t_doom *doom)
{
	int		i;
	t_list	*curr;

	i = -1;
	while (++i < doom->nb.walls)
	{
		doom->walls[i].sect = correct_sector_index(doom, doom->walls[i].sect);
		if (doom->walls[i].n > -1)
			doom->walls[i].n = correct_sector_index(doom, doom->walls[i].n);
	}
	curr = doom->entity;
	while (curr)
	{
		((t_entity *)curr->content)->sector
			= correct_sector_index(doom, ((t_entity *)curr->content)->sector);
		curr = curr->next;
	}
	doom->player.sector = correct_sector_index(doom, doom->player.sector);
}