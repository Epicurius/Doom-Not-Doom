/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:13:50 by jsalmi            #+#    #+#             */
/*   Updated: 2019/11/27 16:19:36 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strnchr(const char *str, int c, size_t n)
{
	size_t	i;
	char	*newstr;

	newstr = (char *)str;
	i = 0;
	while (newstr[i] && newstr[i] != c && i < n)
		i++;
	if (newstr[i] != c)
		return (0);
	return (&newstr[i]);
}
