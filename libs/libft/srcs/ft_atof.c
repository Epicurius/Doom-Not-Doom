/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libft.h"

double	ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;

	c = (char *)str;
	res = (double)ft_atoi(c);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	res2 = (double)ft_atoi(c);
	len = ft_strlen(c);
	while (len--)
		res2 /= 10;
	if (str[0] == '-')
		res2 = -res2;
	return (res + res2);
}

/*
double	ft_atof(const char *str)
{
	double	integral;
	double	fractal;
	char	*c;
	int		len;

	c = (char *)str;
	integral = (double)abs(ft_atoi(c));
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	fractal = (double)abs(ft_atoi(c));
	len = ft_strlen(c);
	while (len--)
		fractal /= 10;
	if (str[0] == '-')
		return ((integral + fractal) * -1);
	return (integral + fractal);
}
*/
