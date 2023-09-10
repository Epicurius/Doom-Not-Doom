/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Authors: Jony Salmi <jony.salmi@gmail.com>
 *          Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "./libft.h"

void	add_to_list(t_list **list, void *new_v, size_t size)
{
	t_list	*lst;

	lst = ft_lstnew(0, 0);
	lst->content = new_v;
	lst->content_size = size;
	if (*list == NULL)
		*list = lst;
	else
		ft_lstadd(list, lst);
}
