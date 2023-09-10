/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

int	ft_wordcount(const char *s, char c)
{
	int	wc;
	int	i;

	i = 0;
	wc = 0;
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			wc++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (wc);
}
