/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libm.h"

/*
 *	Print t_v2 components.
 */
void	print_v2(char *str, t_v2 v)
{
	if (str)
		ft_printf("%s\t", str);
	ft_printf("[%.2f\t%.2f]\n", v.x, v.y);
}

/*
 *	Print t_v3 components.
 */
void	print_v3(char *str, t_v3 v)
{
	if (str)
		ft_printf("%s\t", str);
	ft_printf("[%.2f\t%.2f\t%.2f]\n", v.x, v.y, v.z);
}
