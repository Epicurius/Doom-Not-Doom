/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Authors: Jony Salmi <jony.salmi@gmail.com>
 *          Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libui.h"

void	ui_label_new(t_ui_window *win, t_ui_element *label)
{
	t_ui_label			*lab;

	ui_element_new(win, label);
	label->element = ft_memalloc(sizeof(t_ui_label));
	label->element_type = UI_TYPE_LABEL;
	lab = label->element;
	lab->text = ft_strdup("label text");
	lab->text_align = UI_TEXT_ALIGN_NONE;
	lab->font_path = ft_strdup(DEFAULT_TTF"DroidSans.ttf");
	lab->font_size = 12;
	lab->font_color = 0xff037171;
	lab->max_w = -1;
	lab->font = NULL;
	lab->font_recreate = 1;
	lab->texture_recreate = 1;
}

/*
 * Only made so it wouldnt spam the chat.
 *
 * We are only making blank event handler for label,
 * because the ui_layout event handler doesn't like when
 * an element doesn't have one.
*/
void	ui_label_event(t_ui_element *elem, SDL_Event e)
{
	(void)elem;
	(void)e;
}

int	ui_label_render(t_ui_element *elem)
{
	t_ui_label	*label;

	if (!ui_element_render(elem))
		return (0);
	label = elem->element;
	if (label->texture_recreate || elem->win->textures_recreate)
	{
		ui_label_texture_redo(elem);
		ui_label_text_align(elem, label->text_align);
	}
	return (1);
}

void	ui_label_free(void *elem, size_t size)
{
	t_ui_element	*element;
	t_ui_label		*label;

	element = elem;
	if (!element)
		return ;
	label = element->element;
	if (!label)
		return ;
	ft_strdel(&label->text);
	ft_strdel(&label->font_path);
//	TTF_CloseFont(label->font);
	free(label);
	(void)size;
}
