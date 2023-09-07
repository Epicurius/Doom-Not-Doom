/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libpf.h"

int	ft_vprintf(const char *restrict format, va_list ap)
{
	return (ft_vfprintf(stdout, format, ap));
}

int	ft_printf(const char *restrict format, ...)
{
	va_list	ap;
	int		len;

	if (!format)
		return (-1);
	va_start(ap, format);
	len = ft_vfprintf(stdout, format, ap);
	va_end(ap);
	return (len);
}
