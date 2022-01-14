/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 09:49:46 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/16 13:22:23 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
	{
		write(1, "\x1b[31m!![FT_MEMALLOC ERROR]!!\x1b[00m\n", 35);
		exit(1);
	}
	ft_memset(mem, 0, size);
	return (mem);
}
