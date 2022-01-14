/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 16:40:14 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/03 08:39:18 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strreplace(char **dest, char **src)
{
	if (!src || *src == NULL)
		return (0);
	if (dest)
		ft_strdel(dest);
	*dest = ft_strdup(*src);
	ft_strdel(src);
	return (1);
}
