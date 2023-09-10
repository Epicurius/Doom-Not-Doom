/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Authors: Jony Salmi <jony.salmi@gmail.com>
 *          Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "./libft.h"

int	ft_strendswith(char const *src, char const *comp)
{
	int	src_len;
	int	comp_len;

	src_len = ft_strlen(src);
	comp_len = ft_strlen(comp);
	if (src_len < comp_len)
		return (1);
	return (ft_strcmp(src + src_len - comp_len, comp));
}
