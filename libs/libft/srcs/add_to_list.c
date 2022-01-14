/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:31:50 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/11 10:09:11 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
