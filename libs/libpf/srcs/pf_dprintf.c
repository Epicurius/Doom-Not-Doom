/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin
 */

# include "libpf.h"

int	ft_dprintf(int fd, const char *restrict format, ...)
{
	FILE	*fp;
	va_list	ap;
	int		len;

	if (!format || fd < 0)
		return (-1);
	fp = fdopen(fd, "a");
	if (fp == NULL)
		return (-2);
	va_start(ap, format);
	len = ft_vfprintf(fp, format, ap);
	va_end(ap);
	fclose(fp);
	return (len);
}

int	ft_vdprintf(int fd, const char *restrict format, va_list ap)
{
	FILE	*fp;
	int		len;

	if (!format || fd < 0)
		return (-1);
	fp = fdopen(fd, "a");
	if (fp == NULL)
		return (-2);
	len = ft_vfprintf(fp, format, ap);
	fclose(fp);
	return (len);
}