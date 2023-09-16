/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

/*
 * All elements should be in stack memory,
 * and you should pass in the address of it to this function,
 * which then reset the values to the default values.
 *
 * NOTE: if you resize the element, you have to update the texture.
*/
void	ui_element_new(t_ui_window *win, t_ui_element *elem)
{
	memset(elem, 0, sizeof(t_ui_element));
	elem->win = win;
	elem->pos = vec4(0, 0, 50, 20);
	elem->state = UI_STATE_DEFAULT;
	elem->colors[UI_STATE_DEFAULT] = 0xff95D7AE;
	elem->colors[UI_STATE_HOVER] = 0xff7BAE7F;
	elem->colors[UI_STATE_CLICK] = 0xff73956F;
	elem->images[UI_STATE_DEFAULT] = NULL;
	elem->images[UI_STATE_HOVER] = NULL;
	elem->images[UI_STATE_CLICK] = NULL;
	elem->use_images = 0;
	elem->texture_recreate = 1;
	ui_element_set_parent(elem, win, UI_TYPE_WINDOW);
	elem->element = NULL;
	elem->element_type = UI_TYPE_ELEMENT;
	elem->show = 1;
	elem->event = 1;
	elem->last_state = -999;
	elem->children = NULL;
	elem->figure_out_z = 1;
	elem->free_me = 1;
}

void	ui_element_free(void *elem_p, size_t size)
{
	t_ui_element	*elem;

	elem = elem_p;
	if (!elem)
		return ;
	if (g_acceptable[elem->element_type].freer)
		g_acceptable[elem->element_type].freer(elem, elem->element_type);
	elem->element = NULL;
	ui_element_textures_free(elem);
	ui_element_images_free(elem);
	SDL_DestroyTexture(elem->texture);
	elem->win = NULL;
	elem->parent_screen_pos = NULL;
	if (elem->id)
		ft_strdel(&elem->id);
	elem->parent_rendered_last_frame = NULL;
	ui_element_remove_child_from_parent(elem);
	ui_list_element_free(&elem->children);
	elem->children = NULL;
	if (elem->free_me && !elem->is_a_part_of_another)
		free(elem);
	(void)size;
}
