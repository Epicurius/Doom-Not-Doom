/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/14 12:13:28 nneronin
 * Updated: 2021/05/15 20:34:53 nneronin
 */

#include "libpf.h"

static void	set_padding(t_pf *p)
{
	p->padding.size = 1;
	if (!p->flag.minus && p->flag.zero)
		p->padding.zeros = p->min_width - p->padding.size;
	space_padding(p, 0);
}

void	pf_char(t_pf *p)
{
	char	c;

	c = va_arg(p->ap, int);
	set_padding(p);
	put_left_spaces(p);
	put_zeros(p);
	fill_buffer(p, &c, 1);
	put_right_spaces(p);
}
