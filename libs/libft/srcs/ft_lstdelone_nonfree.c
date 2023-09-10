/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Authors: Jony Salmi <jony.salmi@gmail.com>
 *          Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

void	ft_lstdelone_nonfree(t_list **lst, t_list *del)
{
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
	free(del);
}
