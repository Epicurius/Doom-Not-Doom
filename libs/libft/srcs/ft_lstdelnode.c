/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:46:48 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/11 10:09:49 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstnodedel(t_list **alst, void (*del)(void*, size_t))
{
	if (alst == NULL)
		return ;
	(*alst)->prev->next = (*alst)->next;
	(*alst)->next->prev = (*alst)->prev;
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
