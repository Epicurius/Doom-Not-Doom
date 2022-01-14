# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 11:13:47 by nneronin          #+#    #+#              #
#    Updated: 2021/12/09 13:40:52 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED		:= "\e[0;31m"
GREEN	:= "\e[0;32m"
YELLOW	:= "\e[0;33m"
BLUE	:= "\e[0;34m"
MAGENTA	:= "\e[0;35m"
CYAN	:= "\e[0;36m"
RESET	:= "\e[0m"

RAW =	add_to_list.c\
		ft_atof.c\
		ft_atoi.c\
		ft_atoi_base.c\
		ft_arraydel.c\
		ft_arrlen.c\
		ft_arrjoin.c\
		ft_b_itoa.c\
		ft_b_ftoa.c\
		ft_bzero.c\
		ft_clamp.c\
		ft_compile_string.c\
		ft_dellstnode.c\
		ft_filetostr.c\
		ft_ftoa.c\
		ft_get_file_content.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_islower.c\
		ft_isprint.c\
		ft_isspace.c\
		ft_isupper.c\
		ft_iswspace.c\
		ft_itoa.c\
		ft_itoa_base.c\
		ft_lstadd.c\
		ft_lstadd_new.c\
		ft_lstcontains.c\
		ft_lstdel.c\
		ft_lstdelnode.c\
		ft_lstdelone.c\
		ft_lstiter.c\
		ft_lstlen.c\
		ft_lstmap.c\
		ft_lstnew.c\
		ft_memalloc.c\
		ft_memccpy.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memdel.c\
		ft_memdup.c\
		ft_memmove.c\
		ft_memset.c\
		ft_min_max.c\
		ft_nbrlen.c\
		ft_nstrstr.c\
		ft_pow.c\
		ft_putarr.c\
		ft_putchar.c\
		ft_putchar_fd.c\
		ft_putendl.c\
		ft_putendl_fd.c\
		ft_putnbr.c\
		ft_putnbr_fd.c\
		ft_putnchar.c\
		ft_putnstr.c\
		ft_putstr.c\
		ft_putstr_fd.c\
		ft_pythagoras.c\
		ft_readtostr.c\
		ft_realloc.c\
		ft_reverse.c\
		ft_stradd.c\
		ft_straddchar.c\
		ft_strarr_func.c\
		ft_strcat.c\
		ft_strchr.c\
		ft_strchrlen.c\
		ft_strclr.c\
		ft_strnclr.c\
		ft_strcmp.c\
		ft_strcpy.c\
		ft_strcut.c\
		ft_strdel.c\
		ft_strdup.c\
		ft_strendswith.c\
		ft_strequ.c\
		ft_stringsplit.c\
		ft_striter.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strjoiner.c\
		ft_strjoinf.c\
		ft_strlcat.c\
		ft_strlen.c\
		ft_strmap.c\
		ft_strmapi.c\
		ft_strncat.c\
		ft_strnchr.c\
		ft_strncmp.c\
		ft_strncpy.c\
		ft_strndup.c\
		ft_strnequ.c\
		ft_strnew.c\
		ft_strnrev.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strremove.c\
		ft_strreplace.c\
		ft_strrev.c\
		ft_strsplit.c\
		ft_strspn.c\
		ft_strstr.c\
		ft_strsub.c\
		ft_strtoupper.c\
		ft_strtrim.c\
		ft_swap.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_wordcount.c\
		ft_timer_func.c\
		ft_lstdelone_nonfree.c\
		get_next_line.c

NAME = libft.a
CDIR = srcs
IDIR = -I.
ODIR = objs
SRCS = $(addprefix $(CDIR)/, $(RAW))
OBJS = $(addprefix $(ODIR)/, $(RAW:.c=.o))
CFLAGS = -Wall -Wextra -Werror -MMD -O3

all: $(NAME)
	@printf $(GREEN)"\e[J[INFO] $(NAME) ready!\n"$(RESET)

$(ODIR):
	@mkdir -p $(ODIR)

$(ODIR)/%.o: $(CDIR)/%.c
	@printf $(YELLOW)"\e[JCompiling $<\n\e[F"$(RESET)
	@gcc -c $< -o $@ $(CFLAGS) $(IDIR)

$(NAME): $(ODIR) $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

clean: 
	@printf $(CYAN)"[INFO] $(NAME) cleaned!\n"$(RESET)
	@rm -rf $(ODIR)

fclean: clean
	
	@rm $(NAME)

re: fclean all

.PHONY: fclean all clean re $(NAME)
