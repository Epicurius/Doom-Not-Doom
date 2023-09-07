/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#ifndef LIBPF_H
# define LIBPF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <errno.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>

# define FT_ERROR(...)	pf_error(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
# define FT_INFO(...)	pf_info(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

# define PF_BUFF_SIZE	2048

typedef struct s_padding
{
	int			left_spaces;
	int			sign;
	int			zeros;
	int			size;
	int			right_spaces;
}				t_padding;

typedef struct s_flag
{
	uint8_t		minus;
	uint8_t		plus;
	uint8_t		zero;
	uint8_t		space;
	uint8_t		hash;
}				t_flag;

typedef struct s_pf
{
	FILE			*fp;
	va_list			ap;
	t_flag			flag;
	t_padding		padding;
	char			*format;
	char			*buffer;
	unsigned int	size;
	const char		*invalid;
	unsigned int	chars;
	int				print_len;
	int				min_width;
	int				precision;
	int				size_bytes;
	uint8_t			caps;
}					t_pf;

/* File: srcs/error_msg.c */
void		error_msg(const char *restrict format, ...);
void		pf_error(char *file, char *func, int line,
				const char *restrict format, ...);
void		pf_info(char *file, char *func, int line,
				const char *restrict format, ...);
/* File: srcs/ft_asprintf.c */
int			ft_asprintf(char **restrict ptr, const char *restrict format,
				...);
/* File: srcs/ft_dprintf.c */
int			ft_dprintf(int fd, const char *restrict format, ...);
int			ft_vdprintf(int fd, const char *restrict format, va_list ap);
/* File: srcs/ft_fprintf.c */
int			ft_vfprintf(FILE *fp, const char *restrict format, va_list ap);
int			ft_fprintf(FILE *fp, const char *restrict format, ...);
/* File: srcs/ft_sprintf.c */
int			ft_sprintf(char *str, const char *restrict format, ...);
int			ft_snprintf(char *str, int len, const char *restrict format, ...);
/* File: srcs/pf_base.c */
void		pf_base(t_pf *p, unsigned long nb, char *base);
/* File: srcs/pf_buffer.c */
void		fill_buffer(t_pf *p, const char *s, unsigned int size);
/* File: srcs/pf_char.c */
void		pf_char(t_pf *p);
/* File: srcs/pf_flags.c */
void		put_left_spaces(t_pf *p);
void		put_sign(t_pf *p, long nb);
void		put_zeros(t_pf *p);
void		put_right_spaces(t_pf *p);
/* File: srcs/pf_float.c */
void		pf_float(t_pf *p);
/* File: srcs/pf_format.c */
void		pf_read_format(const char *format, t_pf *p);
/* File: srcs/pf_formats1.c */
void		read_flags(t_pf *p);
void		read_width(t_pf *p);
void		read_precision(t_pf *p);
void		read_wildcard(t_pf *p);
/* File: srcs/pf_formats2.c */
void		specifier_sorter(t_pf *p, int c);
void		read_size(t_pf *p);
void		pf_invalid(t_pf *p);
/* File: srcs/pf_init.c */
void		pf_init(t_pf *p, FILE *fd, char *buffer, int size);
/* File: srcs/pf_nbr.c */
void		pf_nbr(t_pf *p);
/* File: srcs/pf_nbr_inf.c */
int			pf_nbr_inf(t_pf *p, long double nb);
/* File: srcs/pf_nbr_o.c */
void		set_zeros_base(t_pf *p, unsigned long nb, int base_len);
void		pf_nbr_o(t_pf *p);
/* File: srcs/pf_nbr_p.c */
void		pf_nbr_p(t_pf *p);
/* File: srcs/pf_nbr_u.c */
void		pf_nbr_u(t_pf *p);
/* File: srcs/pf_nbr_x.c */
void		pf_nbr_x(t_pf *p);
/* File: srcs/pf_padding.c */
void		space_padding(t_pf *p, int extra);
void		set_float_padding(t_pf *p, long i_part, long double nb);
/* File: srcs/pf_percent.c */
void		pf_putpercent(t_pf *p);
/* File: srcs/pf_printf.c */
int			ft_vprintf(const char *restrict format, va_list ap);
int			ft_printf(const char *restrict format, ...);
/* File: srcs/pf_reset.c */
void		reset_options(t_pf *p);
/* File: srcs/pf_specials.c */
void		pf_specials(t_pf *p);
/* File: srcs/pf_str.c */
void		pf_str(t_pf *p);
void		pf_str(t_pf *p);


typedef struct s_pf_style
{
	char		*str;
	char		*code;
	int			len;
}				t_pf_style;

#endif
