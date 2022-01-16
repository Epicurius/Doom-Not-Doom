/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_input_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:23:14 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:23:15 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

t_ui_input	*ui_input_get(t_ui_element *elem)
{
	if (elem->element_type != UI_TYPE_INPUT)
	{
		ft_printf("[%s] Elem not of type UI_TYPE_INPUT. %d %s.\n",
			__FUNCTION__, elem->element_type,
			ui_element_type_to_string(elem->element_type));
		return (NULL);
	}
	return (elem->element);
}

t_ui_element	*ui_input_get_label_element(t_ui_element *elem)
{
	if (!elem)
		return (NULL);
	return (&((t_ui_input *)elem->element)->label);
}

t_ui_label	*ui_input_get_label(t_ui_element *elem)
{
	return (ui_input_get_label_element(elem)->element);
}
