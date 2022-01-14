/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 16:51:09 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/03 09:04:27 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nstrstr(char *str1, char *str2)
{
	int	i;
	int	k;

	i = 0;
	k = ft_strlen(str1) - ft_strlen(str2);
	while (str1[k + i] != '\0')
	{
		if (str1[k + i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}
