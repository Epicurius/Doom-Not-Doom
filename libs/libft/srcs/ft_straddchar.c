/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Authors: Jony Salmi <jony.salmi@gmail.com>
 *          Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

void	ft_straddchar(char **str, char c)
{
	char	*temp;

	temp = ft_strnew(1);
	temp[0] = c;
	if (*str == NULL)
		*str = ft_strdup(temp);
	else
		ft_stradd(str, temp);
	ft_strdel(&temp);
}
