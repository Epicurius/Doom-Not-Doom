/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/23 17:58:07 nneronin
 * Updated: 2021/04/29 13:58:23 nneronin
 */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst);
		lst = lst->next;
	}
}
