/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_dropdown.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:22:22 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/13 13:14:35 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_dropdown_new(t_ui_window *win, t_ui_element *elem)
{
	t_ui_dropdown	*drop;

	ui_element_new(win, elem);
	elem->element = ft_memalloc(sizeof(t_ui_dropdown));
	elem->element_type = UI_TYPE_DROPDOWN;
	drop = elem->element;
	ui_label_new(win, &drop->label);
	drop->label.is_a_part_of_another = 1;
	ui_label_set_text(&drop->label, "Dropdown");
	ui_element_set_parent(&drop->label, elem, UI_TYPE_ELEMENT);
	ui_menu_new(win, &drop->menu);
	drop->menu.is_a_part_of_another = 1;
	ui_element_pos_set(&drop->menu,
		vec4(0, elem->pos.h, drop->menu.pos.w, drop->menu.pos.h));
	drop->menu.show = 0;
	((t_ui_menu *)drop->menu.element)->event_children = 1;
	((t_ui_menu *)drop->menu.element)->render_children = 1;
	ui_element_set_parent(&drop->menu, elem, UI_TYPE_ELEMENT);
	drop->max_h = 100;
	ui_scrollbar_new(win, &drop->scrollbar);
	drop->scrollbar.is_a_part_of_another = 1;
	ui_element_set_parent(&drop->scrollbar, elem, UI_TYPE_ELEMENT);
	ui_scroll_value_set(&drop->scrollbar, 0);
	((t_ui_scrollbar *)drop->scrollbar.element)->target = &drop->menu;
	((t_ui_scrollbar *)drop->scrollbar.element)->top_most = vec2i(0, 0);
}

void	ui_dropdown_edit(t_ui_element *elem, t_ui_recipe *recipe)
{
	t_ui_dropdown	*drop;

	if (!elem || !recipe)
		return ;
	drop = elem->element;
	ui_label_edit(&drop->label, recipe);
}

int	ui_dropdown_render(t_ui_element *elem)
{
	t_ui_dropdown	*drop;
	t_ui_element	*scroll_button;

	if (!ui_button_render(elem))
		return (0);
	drop = elem->element;
	drop->drop_exit = 0;
	drop->menu.z = elem->z;
	ui_element_pos_set(&drop->menu,
		vec4(0, elem->pos.h,
			drop->menu.pos.w, ft_min(drop->max_h, drop->menu.pos.h)));
	ui_menu_render(&drop->menu);
	ui_element_pos_set(&drop->scrollbar,
		vec4(drop->menu.pos.x + drop->menu.pos.w, elem->pos.h,
			10, drop->menu.pos.h));
	scroll_button = ui_scrollbar_get_button_element(&drop->scrollbar);
	ui_element_pos_set(scroll_button,
		vec4(scroll_button->pos.x, scroll_button->pos.y,
			drop->scrollbar.pos.w, scroll_button->pos.h));
	ui_scrollbar_render(&drop->scrollbar);
	return (1);
}

void	ui_dropdown_free(void *elem, size_t size)
{
	t_ui_element	*element;
	t_ui_dropdown	*dropdown;

	element = elem;
	if (!element)
		return ;
	dropdown = element->element;
	if (!dropdown)
		return ;
	ui_element_free(&dropdown->label, UI_TYPE_LABEL);
	ui_element_free(&dropdown->menu, UI_TYPE_MENU);
	ui_element_free(&dropdown->scrollbar, UI_TYPE_SCROLLBAR);
	free(dropdown);
	(void)size;
}

void	ui_dropdown_activate(t_ui_element *drop, t_ui_element *elem)
{
	t_list			*curr;
	t_ui_dropdown	*d;

	if (!elem)
		return ;
	d = ui_dropdown_get_dropdown(drop);
	if (!drop || !d)
		return ;
	curr = ui_dropdown_get_menu_element(drop)->children;
	while (curr)
	{
		if (elem == curr->content)
		{
			d->active = elem;
			ui_button_toggle_on(d->active);
			ui_element_render(d->active);
			ui_label_set_text(&d->label, ui_button_get_label(d->active)->text);
			break ;
		}
		curr = curr->next;
	}
}
