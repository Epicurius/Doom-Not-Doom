/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:49:34 by jsalmi            #+#    #+#             */
/*   Updated: 2021/07/03 08:58:49 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_strendswith(char const *src, char const *comp)
{
	int	src_len;
	int	comp_len;

	src_len = ft_strlen(src);
	comp_len = ft_strlen(comp);
	if (src_len < comp_len)
		return (1);
	return (ft_strcmp(src + src_len - comp_len, comp));
}
