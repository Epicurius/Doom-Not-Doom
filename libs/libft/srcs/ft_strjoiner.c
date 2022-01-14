/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoiner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 14:50:47 by nneronin          #+#    #+#             */
/*   Updated: 2020/09/24 16:26:45 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

char	*ft_strjoiner(char *first, ...)
{
	char	*tmp;
	char	*str;
	char	*curr;
	va_list	ap;

	if (first == NULL)
		return (NULL);
	va_start(ap, first);
	str = ft_strdup(first);
	curr = va_arg(ap, char *);
	while (curr != NULL)
	{
		tmp = ft_strdup(str);
		free(str);
		str = ft_strjoin(tmp, curr);
		free(tmp);
		curr = va_arg(ap, char *);
	}
	va_end(ap);
	return (str);
}
