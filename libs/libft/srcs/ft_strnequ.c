/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (ft_strncmp(s1, s2, n))
		return (0);
	return (1);
}
