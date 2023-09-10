/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"
#include <stdio.h>

static void	wc_and_cc(char *str, char c, int *wc, int *cc)
{
	*cc = 0;
	*wc = 0;
	while (*str)
	{
		if (*str && *str != c)
		{
			*wc += 1;
			while (*str && *str != c)
			{
				str++;
				*cc += 1;
			}
		}
		else
			str++;
	}
}

static char	**split(char *str, char c, int wc, int cc)
{
	void		*arr;
	const char	**ptrs;
	char		*data;

	arr = malloc(8 * (wc + 1) + (cc + wc));
	if (!arr)
		return (NULL);
	ptrs = arr;
	data = arr + 8 * (wc + 1);
	while (*str)
	{
		if (*str != c)
		{
			*ptrs = data;
			while (*str && *str != c)
				*data++ = *str++;
			*data = '\0';
			data++;
			*++ptrs = NULL;
		}
		else
			str++;
	}
	return (arr);
}

char	**stringsplit(const char *s, char c, int *nb)
{
	int		wc;
	int		cc;
	char	*str;

	str = (char *)s;
	wc_and_cc(str, c, &wc, &cc);
	if (nb)
		*nb = wc;
	return (split(str, c, wc, cc));
}
