/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/04/30 13:17:44 nneronin
 * Updated: 2021/12/15 10:21:53 nneronin
 */

#include "libft.h"

t_list	*ft_dellstnode(t_list **lst, t_list *del)
{
	t_list	*next;

	next = NULL;
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
	if ((*lst))
		next = del->next;
	free(del->content);
	free(del);
	return (next);
}
