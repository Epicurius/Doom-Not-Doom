/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/23 16:03:47 nneronin
 * Updated: 2021/04/29 14:21:58 nneronin
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
