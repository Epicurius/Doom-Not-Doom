/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjointf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:39:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/17 16:38:23 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
