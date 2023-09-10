/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ui_recipe_free(void *recipe, size_t size)
{
	t_ui_recipe	*rcp;
	int			iii;

	rcp = recipe;
	if (!rcp)
		return ;
	ft_strdel(&rcp->id);
	iii = -1;
	while (++iii < UI_STATE_AMOUNT)
		if (rcp->bg_images_set[iii] && rcp->bg_images[iii])
			ft_strdel(&rcp->bg_images[iii]);
	ft_strdel(&rcp->title);
	ft_strdel(&rcp->font);
	ft_arraydel(rcp->flags);
	ft_strdel(&rcp->placeholder_text);
	ft_strdel(&rcp->target);
	free(rcp);
	(void)size;
}
