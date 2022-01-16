/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_radio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:04 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:24:05 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_radio_new(t_ui_window *win, t_ui_element *elem)
{
	t_ui_radio	*radio;

	ui_element_new(win, elem);
	ui_element_pos_set(elem, vec4(elem->pos.x, elem->pos.y, 0, 0));
	radio = ft_memalloc(sizeof(t_ui_radio));
	radio->elem = elem;
	elem->element = radio;
	elem->element_type = UI_TYPE_RADIO;
	radio->active = NULL;
}

void	ui_radio_event(t_ui_element *elem, SDL_Event e)
{
	t_ui_radio		*radio;
	t_list			*curr;

	if (!elem->show || !*elem->parent_show)
		return ;
	radio = elem->element;
	ui_list_radio_event(elem->children, &radio->active);
}

/*
 * Assumes everything in list is t_ui_element, and preferably t_ui_button type;
 * Return: if a new active 1 else 0;
 *
 * If we have set active outside this function this still
 * 	toggles it on (so dont remove the last if(*active)...;
*/
int	ui_list_radio_event(t_list *list, t_ui_element **active)
{
	t_ui_element	*elem;
	int				result;

	result = 0;
	while (list)
	{
		elem = list->content;
		elem->is_toggle = 0;
		if (elem->was_click)
		{
			if (*active != elem)
				result = 1;
			*active = elem;
		}
		else if (elem->is_hover)
			elem->state = UI_STATE_HOVER;
		else
			elem->state = UI_STATE_DEFAULT;
		list = list->next;
	}
	ui_button_toggle_on(*active);
	return (result);
}

/*
 * radio will only update its screen position so that
 * its children render correctly.
 * and ofc check if the parent of this elem was shown/renderer and
 * 	other stuff that the renderer checks;
*/
int	ui_radio_render(t_ui_element *elem)
{
	if (!ui_element_render(elem))
		return (0);
	return (1);
}

void	ui_radio_free(void *elem, size_t size)
{
	t_ui_element	*element;
	t_ui_radio		*radio;

	element = elem;
	if (!element)
		return ;
	radio = element->element;
	if (!radio)
		return ;
	free(radio);
	(void)size;
}
