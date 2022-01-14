/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:00:24 by nneronin          #+#    #+#             */
/*   Updated: 2020/09/24 15:01:03 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	charset_i;
	size_t	str_i;
	int		found;

	str_i = 0;
	found = 0;
	while (s[str_i])
	{
		charset_i = 0;
		while (accept[charset_i])
		{
			if (accept[charset_i] == s[str_i])
				found = 1;
			charset_i++;
		}
		if (!found)
			return (str_i);
		found = 0;
		str_i++;
	}
	return (str_i);
}
