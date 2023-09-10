/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

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
