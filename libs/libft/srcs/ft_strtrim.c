/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Authors: Jony Salmi <jony.salmi@gmail.com>
 *          Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "./libft.h"

char	*ft_strtrim(char const *str)
{
	int		i;
	int		j;
	int		total;
	char	*final;

	i = -1;
	while (str[++i] && ft_isspace(str[i]))
		;
	j = ft_strlen(str);
	while (str[--j] && ft_isspace(str[j]))
		;
	total = j - i + 1;
	if (total <= 0)
		return (NULL);
	final = malloc(sizeof(char) * (total + 1));
	ft_strncpy(final, str + i, total);
	final[total] = '\0';
	return (final);
}
