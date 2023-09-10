/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

char	*ft_strcut(char *str, int start, int end)
{
	char	*new;
	int		i;

	if (!str)
		return (NULL);
	if (end <= 0)
		end = ft_strlen(str);
	new = (char *)malloc(end - start + 1);
	if (!new)
		return (NULL);
	i = start;
	while (i < end)
	{
		new[i - start] = str[i];
		i++;
	}
	new[i - start] = '\0';
	free(str);
	return (new);
}
