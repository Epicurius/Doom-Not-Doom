/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_nonfree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:09:41 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/11 10:09:43 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
