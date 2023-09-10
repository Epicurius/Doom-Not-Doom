/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

t_list	*ft_dellstnode(t_list **lst, t_list *del)
{
	t_list	*next;

	next = NULL;
	if (!del->prev && !del->next)
		(*lst) = NULL;
	else if (del->next && del->prev)
	{
		del->next->prev = del->prev;
		del->prev->next = del->next;
	}
	else if (del->next)
	{
		(*lst) = del->next;
		del->next->prev = NULL;
	}
	else if (del->prev)
		del->prev->next = NULL;
	if ((*lst))
		next = del->next;
	free(del->content);
	free(del);
	return (next);
}
