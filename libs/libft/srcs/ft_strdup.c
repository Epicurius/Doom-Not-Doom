/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		x;

	x = -1;
	if (!src)
		return (NULL);
	while (src[++x] != '\0')
		;
	dest = malloc(sizeof(char) * (x + 1));
	if (!dest)
		return (NULL);
	x = -1;
	while (src[++x])
		dest[x] = src[x];
	dest[x] = '\0';
	return (dest);
}
