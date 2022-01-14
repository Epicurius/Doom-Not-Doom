/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@stuent.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:14:11 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/08 14:28:03 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_reverse(char *s)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * i);
	if (!str)
		return (0);
	while (i > 0)
	{
		str[j] = s[i - 1];
		i--;
		j++;
	}
	return (str);
}

/*
 * Wont malloc does it on the actual string.
*/
char	*ft_b_reverse(char *s)
{
	int		front;
	int		back;
	char	temp;

	front = -1;
	back = ft_strlen(s) - 1;
	while (++front < back)
	{
		temp = s[front];
		s[front] = s[back - front];
		s[back] = temp;
	}
	return (s);
}
