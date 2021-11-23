/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:18:33 by nneronin          #+#    #+#             */
/*   Updated: 2021/11/23 09:22:24 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Parse type of game mode.
 *	Will have more in the future.
 */
static int	parse_game_mode(char *str)
{
	if (ft_strequ(str, "endless"))
		return (ENDLESS);
	return (STORY);
}

/*
 *	Parse header and malloc amount of vertices, walls adn sectors.
 *	Could use realloc but this is faster, so why not.
 */
void	parse_header(t_doom *doom, int nb, char **arr)
{
	if (nb < 5)
		error_msg("Invalid amount of arguments for event %s\n", arr[0]);
	doom->game.mode = parse_game_mode(arr[1]);
	doom->map_scale = ft_atoi(arr[2]);
	doom->nb.vertices = ft_atoi(arr[3]);
	doom->nb.walls = ft_atoi(arr[4]);
	doom->nb.sectors = ft_atoi(arr[5]);
	doom->nb.entities = 0;
	doom->nb.projectiles = 0;
	doom->nb.rifts = 0;
	doom->orb = NULL;
	doom->entity = NULL;
	doom->rifts = NULL;
	doom->vert = PROT_ALLOC(sizeof(t_v3) * doom->nb.vertices);
	doom->walls = PROT_ALLOC(sizeof(t_wall) * doom->nb.walls);
	doom->sectors = PROT_ALLOC(sizeof(t_sector) * doom->nb.sectors);
}
