/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_vec_both2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:24:46 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:24:47 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	*veci_add(int *result, int *v1, int *v2, size_t size)
{
	size_t	ii;

	ii = 0;
	while (ii < size)
	{
		result[ii] = v1[ii] + v2[ii];
		ii++;
	}
	return (result);
}

int	*veci_sub(int *result, int *v1, int *v2, size_t size)
{
	size_t	ii;

	ii = 0;
	while (ii < size)
	{
		result[ii] = v1[ii] - v2[ii];
		ii++;
	}
	return (result);
}
