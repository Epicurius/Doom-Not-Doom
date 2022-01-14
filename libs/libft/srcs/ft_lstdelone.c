/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/23 10:17:22 jsalmi
 * Updated: 2021/12/11 10:09:40 jsalmi
 */

#include "./libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (!*alst)
		return ;
	if ((*alst)->content)
		del((*alst)->content, (*alst)->content_size);
	(*alst)->content = NULL;
	free(*alst);
	*alst = NULL;
}
