/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:41:55 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/14 17:17:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstadd_new(t_list **list, void *content, size_t content_size)
{
	t_list	*new;

	if (content == NULL)
		return (0);
	new = malloc(sizeof(t_list));
	if (!new)
		exit (1);
	new->content = content;
	new->content_size = content_size;
	ft_lstadd(list, new);
	return (1);
}
