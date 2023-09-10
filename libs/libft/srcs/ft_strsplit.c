/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "../libft.h"

static int	ft_wordlen(char const *str, char c, int x)
{
	int	i;

	i = 0;
	while (str[x] != c && str[x])
	{
		x++;
		i++;
	}
	return (i);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		x[3];

	x[1] = 0;
	x[0] = 0;
	if (!s)
		return (NULL);
	arr = ft_memalloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	while (s[x[0]])
	{
		x[2] = 0;
		if (s[x[0]] != c && s[x[0]])
		{
			arr[x[1]] = ft_memalloc(ft_wordlen(s, c, x[0]) + 1);
			ft_strncpy(arr[x[1]], (s + x[0]), ft_wordlen(s, c, x[0]));
			x[2] += ft_wordlen(s, c, x[0]);
			x[0] += ft_wordlen(s, c, x[0]);
			arr[x[1]][x[2]] = '\0';
			x[1]++;
		}
		else
			x[0]++;
	}
	arr[x[1]] = 0;
	return (arr);
}
