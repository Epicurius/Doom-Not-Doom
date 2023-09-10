/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_label_print(t_ui_element *elem)
{
	t_ui_label	*label;

	if (elem->element_type != UI_TYPE_LABEL)
		return ;
	label = elem->element;
	ft_printf("[%s]\n", __FUNCTION__);
	ft_printf("\ttext : %s\n", label->text);
	ft_printf("\twh : %d %d\n", label->text_wh.x, label->text_wh.y);
	ft_printf("\tfont_path : %s\n", label->font_path);
	ft_printf("\tfont_size : %d\n", label->font_size);
	ft_printf("\tfont_color : %#x\n", label->font_color);
	ft_printf("\tmax_w : %d\n", label->max_w);
	ft_printf("\tfont ? : %d\n", !(!label->font));
	ft_printf("\tfont_recreate : %d\n", label->font_recreate);
	ft_printf("\ttexture_recreate : %d\n", label->texture_recreate);
	ft_printf("\ttext_align : [%d] %s\n", label->text_align,
		text_align_to_str(label->text_align));
}

/*
 * Get
*/
t_ui_label	*ui_label_get_label(t_ui_element *elem)
{
	if (elem->element_type != UI_TYPE_LABEL)
	{
		ft_printf("[%s] Elem not of type UI_TYPE_LABEL.<%d:%s>\n",
			__FUNCTION__, elem->element_type,
			ui_element_type_to_string(elem->element_type));
		return (NULL);
	}
	return (elem->element);
}

void	ui_label_text_center(t_ui_element *elem)
{
	t_ui_label		*label;

	label = elem->element;
	if (!label || elem->element_type != UI_TYPE_LABEL
		|| !label->font || !label->text || !elem->parent)
	{
		if (!label)
			ft_printf("[%s] No label in element.\n", __FUNCTION__);
		else if (elem->element_type != UI_TYPE_LABEL)
			ft_printf("[%s] Elem not of type UI_TYPE_LABEL. <%d>\n",
				__FUNCTION__, elem->element_type);
		else
			ft_printf("[%s] Misc problem (come check).\n", __FUNCTION__);
		return ;
	}
	elem->pos.x = (elem->parent_screen_pos->w / 2) - (label->text_wh.x / 2);
	elem->pos.y = (elem->parent_screen_pos->h / 2) - (label->text_wh.y / 2);
	label->text_align = UI_TEXT_ALIGN_CENTER;
}

char	*ui_label_get_text(t_ui_element *elem)
{
	t_ui_label	*label;

	if (!elem)
		return (NULL);
	if (elem->element_type != UI_TYPE_LABEL)
	{
		ft_printf("[%s] Elem not of type UI_TYPE_LABEL. <%s>\n",
			__FUNCTION__, ui_element_type_to_string(elem->element_type));
		return (NULL);
	}
	label = elem->element;
	if (!label)
		return (NULL);
	return (label->text);
}
