/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:40:54 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/08 15:50:39 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strtrim(char const *str)
{
	int		i;
	int		j;
	int		total;
	char	*final;

	i = -1;
	while (str[++i] && ft_isspace(str[i]))
		;
	j = ft_strlen(str);
	while (str[--j] && ft_isspace(str[j]))
		;
	total = j - i + 1;
	if (total <= 0)
		return (NULL);
	final = malloc(sizeof(char) * (total + 1));
	ft_strncpy(final, str + i, total);
	final[total] = '\0';
	return (final);
}
