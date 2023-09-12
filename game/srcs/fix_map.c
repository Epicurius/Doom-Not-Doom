/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

void	fix_sector_index2(t_doom *doom, unsigned short *sector_index)
{
	int		i;
	t_list	*curr;

	i = -1;
	while (++i < doom->nb.walls)
	{
		doom->walls[i].sect = sector_index[doom->walls[i].sect];
		if (doom->walls[i].n > -1)
			doom->walls[i].n = sector_index[doom->walls[i].n];
	}
	i = -1;
	while (++i < doom->nb.events)
	{
		doom->events[i].trigger_sector
			= sector_index[doom->events[i].trigger_sector];
		doom->events[i].event_sector
			= sector_index[doom->events[i].event_sector];
	}
	curr = doom->entity;
	while (curr)
	{
		((t_entity *)curr->content)->sector
			= sector_index[((t_entity *)curr->content)->sector];
		curr = curr->next;
	}
}

void	fix_sector_index(t_doom *doom)
{
	int				i;
	unsigned short	sector_index[1000];

	i = -1;
	while (++i < doom->nb.sectors)
		sector_index[doom->sectors[i].id] = i;
	fix_sector_index2(doom, sector_index);
	i = -1;
	while (++i < doom->nb.events)
		doom->events[i].sector = &doom->sectors[doom->events[i].event_sector];
	doom->player.sector = sector_index[doom->player.sector];
}
