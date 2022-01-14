/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/07/27 16:31:38 jsalmi
 * Updated: 2021/07/27 16:31:39 jsalmi
 */

#include "libft.h"

int	ft_lstlen(t_list *lst)
{
	int		i;
	t_list	*curr;

	i = 0;
	curr = lst;
	while (curr)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}
