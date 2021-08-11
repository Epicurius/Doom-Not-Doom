/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:52:13 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/11 09:17:46 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_wavemode(t_doom *doom)
{
	t_list		*new;
	t_list		*curr;
	t_entity	*entity;

	curr = doom->entity;
	while (curr)
	{
		entity = curr->content;
		entity->hp = g_entity_data[entity->type].health;
		entity->dest = entity->where;
		entity->state = IDLE;
		if (entity->type == RIFT)
		{
			new = ft_lstnew(curr->content, sizeof(t_entity));
			ft_lstadd(&doom->rifts, new);
			doom->nb.rifts += 1;
		}
		curr = curr->next;
	}
}

static void	re_init(t_doom *doom)
{
	int	x;

	init_scale(doom);
	init_player(doom);
	init_wavemode(doom);
	init_game_mode(doom);
	init_slope_normal(doom);
	shade_palets(doom);
	ft_bzero(&doom->keys, 517);
	x = -1;
	while (++x < doom->nb.threads)
	{
		doom->render[x].sectors = doom->sectors;
		doom->render[x].nb_sectors = doom->nb.sectors;
	}
}

static void	read_type(t_doom *doom, int fd, char *line)
{
	if (ft_strnequ(line, "type:map", 8))
		read_line(doom, fd, parse_header);
	else if (ft_strnequ(line, "type:vertex", 11))
		read_line(doom, fd, parse_vertex);
	else if (ft_strnequ(line, "type:wall", 8))
		read_line(doom, fd, parse_wall);
	else if (ft_strnequ(line, "type:sector", 11))
		read_line(doom, fd, parse_sector);
	else if (ft_strnequ(line, "type:entity", 11))
		read_line(doom, fd, parse_entity);
	else if (ft_strnequ(line, "type:f&c", 8))
		read_line(doom, fd, parse_fc);
	else if (ft_strnequ(line, "type:wsprite", 12))
		read_line(doom, fd, parse_wsprite);
	else if (ft_strnequ(line, "type:event", 10))
		read_line(doom, fd, parse_events);
}

static void	free_file(t_doom *doom)
{
	free_map(doom);
	free_entities(doom);
	free_rifts(doom);
	free_projectiles(doom);
	doom->nb.walls = 0;
	doom->nb.sectors = 0;
	doom->nb.vertices = 0;
	doom->nb.projectiles = 0;
	doom->nb.entities = 0;
	doom->nb.rifts = 0;
	doom->nb.kills = 0;
	doom->player.velocity = new_v3(0, 0, 0);
}

void	reload_map(t_doom *doom, char *file_name)
{
	int		fd;
	char	*line;

	if (!doom->keys[KEY_EQUAL])
		return ;
	free_file(doom);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_msg("File does not exist or could not be opened.\n");
	while (get_next_line(fd, &line))
	{
		read_type(doom, fd, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	free(line);
	close(fd);
	validate_map(doom);
	re_init(doom);
	ft_printf("{CLR:41}[INFO] Map ReLoaded!{RESET}\n");
}
