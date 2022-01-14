/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:09:12 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/08 15:03:23 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				x;
	unsigned char	*asd;
	unsigned char	*qwe;

	if (!s1 || !s2)
		return (1);
	qwe = (unsigned char *)s2;
	asd = (unsigned char *)s1;
	x = 0;
	while (asd[x] != '\0' && qwe[x] != '\0' && asd[x] == qwe[x])
	{
		x++;
	}
	return (asd[x] - qwe[x]);
}
