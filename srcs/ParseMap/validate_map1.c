/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 10:12:36 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/05 07:02:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Find sector for each entity.
 */
int	check_entities(t_doom *doom)
{
	t_list		*curr;

	curr = doom->entity;
	while (curr)
	{
		((t_entity *)curr->content)->sector
			= find_sector(doom->sectors, doom->nb.sectors,
				((t_entity *)curr->content)->where);
		if (((t_entity *)curr->content)->sector < 0)
		{
			ft_printf("{YELLOW}[INFO]{RESET} Entity is outside "
				"map boundaries!\n");
			return (0);
		}
		curr = curr->next;
	}
	return (1);
}

/*
 *	Find player sector.
 */
int	check_player(t_doom *doom)
{
	doom->player.sector = find_sector(doom->sectors,
			doom->nb.sectors, doom->player.where);
	if (doom->player.sector < 0)
	{
		ft_printf("{YELLOW}[INFO]{RESET} Player is outside map boundaries!\n");
		return (0);
	}
	return (1);
}

/*
 *	For each sector:
 *	Calculate sector center.
 *	Fix wall orientation to be clockwise.
 *	Fix wall order, if not possible error.
 *	If sector convex, else error.
 */
int	check_map(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		sector_center(&doom->sectors[i]);
		fix_wall_orientation(&doom->sectors[i]);
		if (!fix_wall_order(&doom->sectors[i]))
			return (0);
		if (!is_convex(&doom->sectors[i]))
			return (0);
	}
	return (1);
}

/*
 *	Main validation function.
 *	Checks if map is valid else free.
 */
int	validate_map(t_doom *doom)
{
	if (check_map(doom)
		&& check_player(doom)
		&& check_entities(doom))
		return (1);
	free_doom(doom);
	return (0);
}
