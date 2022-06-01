/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:58:33 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/17 13:38:12 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

void	map_init(t_launcher *launcher)
{
	t_ui_recipe	*map_button_recipe;

	ft_strcpy(&launcher->root[launcher->rlen], "resources/MAPS/");
	get_files_from_dir_with_file_ending(&launcher->endless_map_names,
		launcher->root, ".dnde");
	get_files_from_dir_with_file_ending(&launcher->story_map_names,
		launcher->root, ".dnds");
	map_button_recipe
		= ui_layout_get_recipe(&launcher->layout, "map_button_prefab");
	init_map_buttons_from_list(launcher->endless_map_names, map_button_recipe,
		ui_layout_get_element(&launcher->layout, "endless_map_menu"));
	launcher->endless_map_buttons
		= ui_layout_get_element(&launcher->layout,
			"endless_map_menu")->children;
	init_map_buttons_from_list(launcher->story_map_names, map_button_recipe,
		ui_layout_get_element(&launcher->layout, "story_map_menu"));
	launcher->story_map_buttons
		= ui_layout_get_element(&launcher->layout, "story_map_menu")->children;
}

void	init_map_buttons_from_list(
		t_list *map_names, t_ui_recipe *rcp, t_ui_element *parent)
{
	t_ui_element	*elem;
	float			amount_x;
	int				i;
	int				butt_gap;
	t_list			*curr;

	i = ft_lstlen(parent->children) - 1;
	butt_gap = 10;
	amount_x = parent->pos.w / (rcp->pos.w + butt_gap + rcp->pos.x);
	while ((int)amount_x * (rcp->pos.w + butt_gap) < parent->pos.w + butt_gap)
		butt_gap++;
	curr = map_names;
	while (curr)
	{
		++i;
		elem = ft_memalloc(sizeof(t_ui_element));
		ui_button_new(parent->win, elem);
		ui_element_set_parent(elem, parent, UI_TYPE_ELEMENT);
		ui_element_edit(elem, rcp);
		ui_element_pos_set2(elem,
			vec2(rcp->pos.x + (i % (int)(amount_x) *(rcp->pos.w + butt_gap)),
				rcp->pos.y + (i / (int)(amount_x) *(rcp->pos.h + butt_gap))));
		ui_button_set_text(elem, curr->content);
		curr = curr->next;
	}
}
