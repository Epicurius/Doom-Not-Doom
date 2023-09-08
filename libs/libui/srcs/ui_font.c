/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

t_list	**ui_global_font(void)
{
	static t_list	*fonts = NULL;

	return (&fonts);
}

void	ui_global_font_free(void)
{
	t_list		*curr;

	curr = *ui_global_font();
	while (curr)
	{
		free(((t_ui_font *)curr->content)->path);
		TTF_CloseFont(((t_ui_font *)curr->content)->font);
		free(curr->content);
		curr = curr->next;
	}
	ft_lstdel(ui_global_font(), &dummy_free_er);
}

/*
 * IMPORTANT:
 *	If you call this anywhere, make sure to call ui_global_font_free(); when
 *		exiting the program;
 */
TTF_Font	*ui_get_font(char *path, int size)
{
	t_list		**fonts;
	t_list		*curr;
	t_ui_font	*new_font;

	if (access(path, F_OK))
		return (NULL);
	fonts = ui_global_font();
	curr = *fonts;
	while (fonts && curr)
	{
		if (((t_ui_font *)curr->content)->size == size)
			if (ft_strequ(((t_ui_font *)curr->content)->path, path))
				return (((t_ui_font *)curr->content)->font);
		curr = curr->next;
	}
	new_font = malloc(sizeof(t_ui_font));
	new_font->path = ft_strdup(path);
	new_font->size = size;
	new_font->font = TTF_OpenFont(path, size);
	add_to_list(fonts, new_font, sizeof(t_ui_font));
	return (new_font->font);
}
