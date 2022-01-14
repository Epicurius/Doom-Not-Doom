/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:31:23 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/27 16:31:25 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtoupper(const char *src)
{
	char	*str;
	int		len;
	int		i;

	if (!src)
		return (NULL);
	i = 0;
	len = ft_strlen(src);
	str = ft_strnew(len);
	while (i < len)
	{
		str[i] = ft_toupper(src[i]);
		i++;
	}
	return (str);
}
