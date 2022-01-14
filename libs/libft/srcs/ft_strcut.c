/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 15:15:16 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/17 16:37:15 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
