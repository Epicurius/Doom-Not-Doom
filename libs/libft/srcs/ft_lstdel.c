/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*nxt;

	tmp = *alst;
	if (alst == NULL)
		return ;
	while (tmp != NULL)
	{
		nxt = tmp->next;
		del(tmp->content, tmp->content_size);
		free(tmp);
		tmp = nxt;
	}
	*alst = NULL;
}
