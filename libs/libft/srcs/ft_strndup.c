/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t len)
{
	size_t	counter;
	char	*sdest;

	counter = 0;
	sdest = (char *)ft_memalloc(sizeof(char) * (len + 1));
	if (!sdest)
		return (NULL);
	while (s1[counter] != '\0' && counter < len)
	{
		sdest[counter] = s1[counter];
		counter++;
	}
	sdest[counter] = '\0';
	return (sdest);
}
