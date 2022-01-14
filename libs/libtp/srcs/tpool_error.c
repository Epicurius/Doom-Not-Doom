/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tpool_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 14:55:22 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 09:09:43 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tpool.h"

int	tpool_error(int i)
{
	write(1, "ERROR tpool: ", 13);
	if (i == -1)
		write(1, "passed function errors, (0 == error).\n", 38);
	else if (i == -2)
		write(1, "pthread_create.\n", 16);
	else if (i == -3)
		write(1, "malloc tpool->thread.\n", 22);
	else if (i == -4)
		write(1, "create_task.\n", 13);
	else if (i == -5)
		write(1, "no function passed to tpool_add.\n", 33);
	else if (i == -6)
		write(1, "nb processors must be > 0.\n", 33);
	return (0);
}
