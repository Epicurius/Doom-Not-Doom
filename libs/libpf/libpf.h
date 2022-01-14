/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpf.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:14:30 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/07 16:47:11 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPF_H
# define LIBPF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <errno.h>
# include <stdint.h>
# include <stdbool.h>

# define PF_BUFF_SIZE	2048

typedef struct s_padding
{
	int				left_spaces;
	int				sign;
	int				zeros;
	int				size;
	int				right_spaces;
}					t_padding;

typedef struct s_flag
{
	uint8_t			minus;
	uint8_t			plus;
	uint8_t			zero;
	uint8_t			space;
	uint8_t			hash;
}					t_flag;

typedef struct s_pf
{
	va_list			ap;
	t_flag			flag;
	t_padding		padding;
	char			*format;
	char			*buffer;
	const char		*invalid;
	int				fd;
	int				chars;
	int				print_len;
	int				min_width;
	int				precision;
	int				size_bytes;
	uint8_t			caps;
}					t_pf;

int					ft_printf(const char *restrict format, ...);
int					ft_dprintf(int fd, const char *restrict format, ...);
char				*ft_sprintf(const char *restrict format, ...);
void				pf_init(t_pf *p, int fd);
void				reset_options(t_pf *p);
void				pf_read_format(const char *format, t_pf *p);
void				read_flags(t_pf *p);
void				read_width(t_pf *p);
void				read_precision(t_pf *p);
void				read_wildcard(t_pf *p);
void				read_size(t_pf *p);
void				specifier_sorter(t_pf *p, int c);
void				put_sign(t_pf *p, long nb);
void				put_zeros(t_pf *p);
void				put_right_spaces(t_pf *p);
void				put_left_spaces(t_pf *p);
void				pf_char(t_pf *p);
void				pf_float(t_pf *p);
void				pf_invalid(t_pf *p);
void				pf_nbr(t_pf *p);
int					pf_nbr_inf(t_pf *p, long double nb);
void				pf_nbr_o(t_pf *p);
void				pf_nbr_u(t_pf *p);
void				pf_nbr_x(t_pf *p);
void				pf_nbr_p(t_pf *p);
void				pf_putpercent(t_pf *p);
void				pf_str(t_pf *p);
void				space_padding(t_pf *p, int extra);
void				pf_base(t_pf *p, unsigned long nb, char *base);
void				pf_specials(t_pf *p);
void				print_code(t_pf *p, char *color, int code_len);
void				fill_buffer(t_pf *p, const char *s, unsigned int size);
void				set_float_padding(t_pf *p, long i_part, long double nb);
void				set_float_padding(t_pf *p, long i_part, long double nb);
void				set_zeros_base(t_pf *p, unsigned long nb, int base_len);

typedef struct s_pf_style
{
	char		*str;
	char		*code;
	int			len;
}				t_pf_style;

typedef struct s_pf_emoji
{
	char		*str;
	wchar_t		code;
	int			len;
}				t_pf_emoji;

#endif
