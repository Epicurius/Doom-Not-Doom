/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/04/29 13:57:49 nneronin
 * Updated: 2021/05/08 14:09:00 nneronin
 */

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
