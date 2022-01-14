/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:17:41 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/08 15:03:23 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			x;
	unsigned char	*asd;
	unsigned char	*qwe;

	qwe = (unsigned char *)s2;
	asd = (unsigned char *)s1;
	x = 0;
	if (n <= 0)
		return (0);
	while (x < n - 1 && asd[x] && qwe[x])
	{
		if (asd[x] != qwe[x])
			return (asd[x] - qwe[x]);
		x++;
	}
	return (asd[x] - qwe[x]);
}
