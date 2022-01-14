/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:50:29 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/08 15:03:23 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	x;
	size_t	y;
	int		slen;
	int		dlen;

	x = 0;
	y = 0;
	slen = ft_strlen(src);
	while (dest[x] && x < size)
	{
		x++;
	}
	dlen = x;
	while (size > (x + 1) && src[y])
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (x < size)
		dest[x] = '\0';
	return (dlen + slen);
}
