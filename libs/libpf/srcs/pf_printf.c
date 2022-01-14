/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:16:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/17 18:27:42 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpf.h"

void	pf_init(t_pf *p, int fd)
{
	ft_bzero(p, sizeof(*p));
	p->chars = 0;
	p->print_len = 0;
	p->fd = fd;
	reset_options(p);
}

int	ft_printf(const char *restrict format, ...)
{
	t_pf	p;
	char	buff[PF_BUFF_SIZE];

	if (!format)
		return (-1);
	pf_init(&p, 1);
	p.buffer = buff;
	va_start(p.ap, format);
	pf_read_format((char *)format, &p);
	write(p.fd, p.buffer, p.chars);
	va_end(p.ap);
	return (p.print_len);
}

int	ft_dprintf(int fd, const char *restrict format, ...)
{
	t_pf	p;
	char	buff[PF_BUFF_SIZE];

	if (!format)
		return (-1);
	pf_init(&p, fd);
	p.buffer = buff;
	va_start(p.ap, format);
	pf_read_format((char *)format, &p);
	write(p.fd, p.buffer, p.chars);
	va_end(p.ap);
	return (p.print_len);
}

char	*ft_sprintf(const char *restrict format, ...)
{
	t_pf	p;
	char	buff[PF_BUFF_SIZE];
	char	*str;

	if (!format)
		return (NULL);
	pf_init(&p, 1);
	p.buffer = buff;
	va_start(p.ap, format);
	pf_read_format((char *)format, &p);
	va_end(p.ap);
	str = ft_strndup(p.buffer, p.chars);
	return (str);
}
