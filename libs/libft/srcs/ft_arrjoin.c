/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Authors: Jony Salmi <jony.salmi@gmail.com>
 *          Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

char	**ft_arrjoin(char **to_this, char **from_this)
{
	char	**arr;
	int		total;
	int		i;
	int		j;

	i = 0;
	j = 0;
	arr = NULL;
	total = ft_arrlen(to_this) + ft_arrlen(from_this) + 1;
	if (total == 1)
		return (NULL);
	arr = ft_memalloc(sizeof(char *) * total);
	while (to_this && to_this[i])
	{
		arr[i] = ft_strdup(to_this[i]);
		i++;
	}
	while (from_this && from_this[j])
	{
		arr[i + j] = ft_strdup(from_this[j]);
		j++;
	}
	return (arr);
}
