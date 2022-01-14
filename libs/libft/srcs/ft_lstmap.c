/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/23 18:43:39 nneronin
 * Updated: 2021/04/29 13:58:55 nneronin
 */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	res = f(lst);
	tmp = res;
	while (lst->next != NULL)
	{
		lst = lst->next;
		tmp->next = f(lst);
		tmp = tmp->next;
	}
	return (res);
}
