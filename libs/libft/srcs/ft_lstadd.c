/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/23 17:28:02 nneronin
 * Updated: 2021/04/30 12:05:43 nneronin
 */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (!new || !alst)
	{
		ft_putstr("[ft_lstadd] No args\n");
		return ;
	}
	if (!(*alst))
	{
		(*alst) = new;
		(*alst)->next = NULL;
		(*alst)->prev = NULL;
	}
	else
	{
		new->next = (*alst);
		new->prev = NULL;
		(*alst)->prev = new;
		(*alst) = new;
	}
}
