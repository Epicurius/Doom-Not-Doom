/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Authors: Jony Salmi <jony.salmi@gmail.com>
 *          Niklas Neronin <niklas.neronin@gmail.com>
 */

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f' || c == '\n');
}
