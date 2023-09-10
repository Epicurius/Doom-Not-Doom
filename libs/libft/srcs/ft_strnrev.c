/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

void	ft_strnrev(char *str, int len)
{
	int		i;
	int		len_tmp;
	char	tmp;

	i = 0;
	len_tmp = len;
	while (i < len)
	{
		tmp = str[i];
		str[i] = str[len - 1];
		str[len - 1] = tmp;
		i++;
		len--;
	}
	str[len_tmp] = '\0';
}
