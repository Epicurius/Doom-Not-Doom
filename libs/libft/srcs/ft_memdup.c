/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:50:50 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/14 10:53:22 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *mem, size_t size)
{
	void	*out;

	out = ft_memalloc(size);
	if (out != NULL)
		ft_memcpy(out, mem, size);
	return (out);
}
