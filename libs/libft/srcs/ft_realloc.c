/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:14:32 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/18 15:45:00 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	if (old_size == new_size)
		return (ptr);
	new = malloc(new_size);
	if (!new)
	{
		ft_memdel(&ptr);
		return (NULL);
	}
	ft_bzero(new, new_size);
	if (ptr)
		new = ft_memmove(new, ptr, old_size);
	ft_memdel(&ptr);
	return (new);
}
