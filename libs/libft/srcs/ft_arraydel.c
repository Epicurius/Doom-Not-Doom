/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Authors: Jony Salmi <jony.salmi@gmail.com>
 *          Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

void	ft_arraydel(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		ft_strdel(&arr[i]);
	free(arr);
	arr = NULL;
}
