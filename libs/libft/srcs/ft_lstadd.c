/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (!new || !alst)
	{
		ft_putstr("[ft_lstadd] No args\n");
		return ;
	}
	if (!(*alst))
	{
		(*alst) = new;
		(*alst)->next = NULL;
		(*alst)->prev = NULL;
	}
	else
	{
		new->next = (*alst);
		new->prev = NULL;
		(*alst)->prev = new;
		(*alst) = new;
	}
}
