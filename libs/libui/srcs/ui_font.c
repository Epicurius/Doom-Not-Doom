/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Authors: Jony Salmi <jony.salmi@gmail.com>
 *          Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libui.h"

typedef struct	s_ui_font
{
	char		*path;
	int			size;
	TTF_Font	*font;
}				t_ui_font;

/*
 * Returns null if path doesnt exits;
*/
TTF_Font	*ui_get_font(char *path, int size)
{
	static t_ui_font	*fonts = NULL;
	static size_t		font_count = 0;
	int					i;

	if (access(path, F_OK))
		return (NULL);
	i = -1;
	while (++i < font_count)
		if (fonts[i].size == size)
			if (ft_strequ(fonts[i].path, path))
				return (fonts[i].font);
	fonts = realloc(fonts, ++font_count * sizeof(t_ui_font));
	fonts[font_count - 1].path = ft_strdup(path);
	fonts[font_count - 1].size = size;
	fonts[font_count - 1].font = TTF_OpenFont(path, size);
	return (fonts[font_count - 1].font);
}
