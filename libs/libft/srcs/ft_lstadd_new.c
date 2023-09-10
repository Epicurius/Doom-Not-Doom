/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

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
