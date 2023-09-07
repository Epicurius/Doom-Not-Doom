/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "tpool.h"

int	tpool_error(int i)
{
	write(1, "ERROR tpool: ", 14);
	if (i == -1)
		write(1, "passed function errors, (0 == error).\n", 39);
	else if (i == -2)
		write(1, "pthread_create.\n", 17);
	else if (i == -3)
		write(1, "malloc tpool->thread.\n", 23);
	else if (i == -4)
		write(1, "create_task.\n", 14);
	else if (i == -5)
		write(1, "no function passed to tpool_add.\n", 34);
	return (0);
}
