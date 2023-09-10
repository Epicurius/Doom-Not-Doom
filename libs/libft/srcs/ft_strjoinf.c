/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

char	*ft_strjoinf(char *s1, const char *s2)
{
	char	*str;

	if (!s1)
		return (0);
	if (!s2)
	{
		ft_strdel(&s1);
		return (0);
	}
	str = ft_strnew((ft_strlen(s1) + ft_strlen(s2)));
	if (!str)
	{
		ft_strdel(&s1);
		return (0);
	}
	if (!(ft_strcpy(str, s1)))
		return (0);
	if (!(ft_strcat(str, s2)))
		return (0);
	ft_strdel(&s1);
	return (str);
}
