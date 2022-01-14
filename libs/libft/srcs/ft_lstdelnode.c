/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/23 10:46:48 nneronin
 * Updated: 2021/12/11 10:09:49 jsalmi
 */

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
