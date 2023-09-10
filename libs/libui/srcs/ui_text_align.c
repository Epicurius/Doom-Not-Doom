/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"
#include "ui_load.h"

#define ALIGN_LEFT "LEFT"
#define ALIGN_RIGHT "RIGHT"
#define ALIGN_TOP "TOP"
#define ALIGN_BOT "BOT"
#define ALIGN_CENTER "CENTER"
#define ALIGN_NONE "NONE"
const char	*center_text_align(int text_align)
{
	if (text_align & UI_TEXT_ALIGN_LEFT)
		return (ALIGN_CENTER" "ALIGN_LEFT);
	if (text_align & UI_TEXT_ALIGN_RIGHT)
		return (ALIGN_CENTER" "ALIGN_RIGHT);
	if (text_align & UI_TEXT_ALIGN_TOP)
		return (ALIGN_CENTER" "ALIGN_TOP);
	if (text_align & UI_TEXT_ALIGN_BOT)
		return (ALIGN_CENTER" "ALIGN_BOT);
	return (ALIGN_CENTER);
}

const char	*left_text_align(int text_align)
{
	if (text_align & UI_TEXT_ALIGN_TOP)
		return (ALIGN_LEFT" "ALIGN_TOP);
	if (text_align & UI_TEXT_ALIGN_BOT)
		return (ALIGN_LEFT" "ALIGN_BOT);
	return (ALIGN_LEFT);
}

const char	*right_text_align(int text_align)
{
	if (text_align & UI_TEXT_ALIGN_TOP)
		return (ALIGN_RIGHT" "ALIGN_TOP);
	if (text_align & UI_TEXT_ALIGN_BOT)
		return (ALIGN_RIGHT" "ALIGN_BOT);
	return (ALIGN_RIGHT);
}

const char	*text_align_to_str(int text_align)
{
	if (text_align & UI_TEXT_ALIGN_CENTER)
		return (center_text_align(text_align));
	else if (text_align & UI_TEXT_ALIGN_LEFT)
		return (left_text_align(text_align));
	else if (text_align & UI_TEXT_ALIGN_RIGHT)
		return (right_text_align(text_align));
	else if (text_align & UI_TEXT_ALIGN_TOP)
		return (ALIGN_TOP);
	else if (text_align & UI_TEXT_ALIGN_BOT)
		return (ALIGN_BOT);
	else if (text_align == 0)
		return (ALIGN_NONE);
	return ("UI_TEXT_ALIGN text not set");
}

int	text_align_getter(char *str)
{
	char	**temp;
	int		result;
	int		i;

	temp = ft_strsplit(str, ' ');
	result = 0;
	i = -1;
	while (temp[++i])
	{
		if (ft_strequ(temp[i], "center"))
			result |= UI_TEXT_ALIGN_CENTER;
		else if (ft_strequ(temp[i], "top"))
			result |= UI_TEXT_ALIGN_TOP;
		else if (ft_strequ(temp[i], "bot"))
			result |= UI_TEXT_ALIGN_BOT;
		else if (ft_strequ(temp[i], "left"))
			result |= UI_TEXT_ALIGN_LEFT;
		else if (ft_strequ(temp[i], "right"))
			result |= UI_TEXT_ALIGN_RIGHT;
		else if (ft_strequ(temp[i], "none"))
			result = UI_TEXT_ALIGN_NONE;
	}
	ft_arraydel(temp);
	return (result);
}
