/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

/*
 * Every function under this is for editing the label.
*/
void	ui_label_set_text(t_ui_element *elem, char *text)
{
	t_ui_label	*lab;

	if (!elem)
		return ;
	lab = elem->element;
	if (lab->text)
		ft_strdel(&lab->text);
	lab->text = ft_strdup(text);
	lab->texture_recreate = 1;
}

void	ui_label_font_set(t_ui_element *label, char *font_path)
{
	t_ui_label	*lab;

	lab = label->element;
	if (lab->font_path)
		ft_strdel(&lab->font_path);
	lab->font_path = ft_strdup(font_path);
	lab->font_recreate = 1;
}

void	ui_label_size_set(t_ui_element *label, size_t size)
{
	t_ui_label	*lab;

	lab = label->element;
	if (lab->font_size != size)
	{
		lab->font_recreate = 1;
		lab->texture_recreate = 1;
	}
	lab->font_size = size;
}

Uint32	ui_label_get_color(t_ui_element *elem)
{
	if (elem->element_type != UI_TYPE_LABEL)
	{
		LG_WARN("Element is not of type UI_TYPE_LABEL. <%d : %s>",
			elem->element_type, ui_element_type_to_string(elem->element_type));
		return (0);
	}
	return (ui_label_get_label(elem)->font_color);
}

void	ui_label_color_set(t_ui_element *label, Uint32 color)
{
	t_ui_label	*lab;

	lab = label->element;
	if (lab->font_color != color)
		lab->texture_recreate = 1;
	lab->font_color = color;
}
