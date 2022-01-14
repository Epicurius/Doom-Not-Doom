/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 13:16:07 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/03 09:00:31 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stradd(char **dest, char *src)
{
	char	*temp;

	if (!src)
		return (0);
	if (!(*dest) || *dest == NULL)
	{
		*dest = ft_strdup(src);
		return (1);
	}
	temp = ft_strdup(*dest);
	ft_strdel(dest);
	*dest = ft_strjoin(temp, src);
	ft_strdel(&temp);
	return (1);
}
