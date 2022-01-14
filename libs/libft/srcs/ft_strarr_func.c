/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:30:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/08 14:30:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strarr_func(char **arr, void (*f)(char **))
{
	int	i;

	i = -1;
	while (arr[++i] != NULL)
		if (f != NULL)
			f(&arr[i]);
	return (i);
}
