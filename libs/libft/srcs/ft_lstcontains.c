/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcontains.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:57:49 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/08 14:09:00 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstcontains(t_list *lst, void *content)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->content == content)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
