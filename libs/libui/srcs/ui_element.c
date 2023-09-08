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
	int				i;

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

/*
void	ui_element_print(t_ui_element *elem)
{
	if (!elem)
	{
		ft_printf("[%s] No element.\n", __FUNCTION__);
		return ;
	}
	ft_printf("[%s]\n", __FUNCTION__);
	ft_printf("\tid : %s\n", elem->id);
	ft_printf("\tpos : ");
	print_vec(elem->pos.v, 4);
	ft_printf("\tscreen_pos : ");
	print_veci(elem->screen_pos.v, 4);
	ft_printf("\tfrom_pos : ");
	print_veci(elem->from_pos.v, 4);
	ft_printf("\tto_pos : ");
	print_veci(elem->to_pos.v, 4);
	ft_printf("\tparent_pos : ");
	print_veci(elem->parent_screen_pos->v, 4);
	ft_printf("\tuse_images : %d\n", elem->use_images);
	ft_printf("\tcolors : %#x %#x %#x\n",
		elem->colors[0], elem->colors[1], elem->colors[2]);
	ft_printf("\tstate : %d\n", elem->state);
	ft_printf("\tlast_state : %d\n", elem->last_state);
	ft_printf("\tparent_type : %s\n",
		ui_element_type_to_string(elem->parent_type));
	if (elem->parent_type == UI_TYPE_ELEMENT)
	{
		ft_printf("\tparent element_type : %s\n",
ui_element_type_to_string(((t_ui_element *)elem->parent)->element_type));
		ft_printf("\tparent z : %d\n", ((t_ui_element *)elem->parent)->z);
	}
	ft_printf("\tz : %d\n", elem->z);
	ft_printf("\tfigure_out_z : %d\n", elem->figure_out_z);
	ft_printf("\tshow : %d\n", elem->show);
	ft_printf("\tevent : %d\n", elem->event);
	ft_printf("\tparent show : %d\n", *elem->parent_show);
	ft_printf("\tis_hover : %d\n", elem->is_hover);
	ft_printf("\tis_click : %d\n", elem->is_click);
	ft_printf("\tis_toggle : %d\n", elem->is_toggle);
	ft_printf("\twas_click : %d\n", elem->was_click);
	ft_printf("\ttexture_recreate : %d\n", elem->texture_recreate);
	ft_printf("\telement_type : %s\n",
		ui_element_type_to_string(elem->element_type));
	ft_printf("\trendered_last_frame : %d\n", elem->rendered_last_frame);
	ft_printf("\trender_me_on_parent : %d\n", elem->render_me_on_parent);
	ft_printf("\tis_a_part_of_another : %d\n", elem->is_a_part_of_another);
	if (g_acceptable[elem->element_type].printer)
		g_acceptable[elem->element_type].printer(elem);
}
*/
