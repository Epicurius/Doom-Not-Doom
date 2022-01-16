/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_menu_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:23:50 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:23:51 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

t_ui_menu	*ui_menu_get_menu(t_ui_element *elem)
{
	if (elem->element_type == UI_TYPE_MENU)
		return (elem->element);
	return (NULL);
}
