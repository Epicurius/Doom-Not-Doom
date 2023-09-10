/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libpf.h"
/*
void	fill_output_buffer(t_pf *p, const char *s, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (p->chars + size >= PF_BUFF_SIZE)
	{
		write(p->fd, p->buffer, p->chars);
		p->chars = 0;
	}
	if (size < PF_BUFF_SIZE)
	{
		while (i < size)
		{
			p->buffer[p->chars] = s[i];
			i++;
			p->chars++;
		}
	}
	else
		write(p->fd, s, size);
}
*/
void	fill_buffer(t_pf *p, const char *s, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (p->print_len != -1)
		p->print_len += size;
	if (p->chars + size > MAX_INT)
		p->print_len = -1;
	if (p->chars + size >= PF_BUFF_SIZE)
	{
		write(p->fd, p->buffer, p->chars);
		p->chars = 0;
	}
	if (size < PF_BUFF_SIZE)
	{
		while (i < size)
		{
			p->buffer[p->chars] = s[i];
			i++;
			p->chars++;
		}
	}
	else
		write(p->fd, s, size);
}
