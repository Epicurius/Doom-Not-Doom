RED		:= "\e[0;31m"
GREEN	:= "\e[0;32m"
YELLOW	:= "\e[0;33m"
BLUE	:= "\e[0;34m"
MAGENTA	:= "\e[0;35m"
CYAN	:= "\e[0;36m"
RESET	:= "\e[0m"

RAW =	add_to_list.c\
		ft_arraydel.c\
		ft_arrjoin.c\
		ft_arrlen.c\
		ft_atof.c\
		ft_atoi.c\
		ft_b_itoa.c\
		ft_bzero.c\
		ft_clamp.c\
		ft_dellstnode.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isspace.c\
		ft_isupper.c\
		ft_itoa.c\
		ft_lstadd.c\
		ft_lstadd_new.c\
		ft_lstdel.c\
		ft_lstdelone_nonfree.c\
		ft_lstlen.c\
		ft_lstnew.c\
		ft_memalloc.c\
		ft_memcpy.c\
		ft_memdel.c\
		ft_memmove.c\
		ft_memset.c\
		ft_min_max.c\
		ft_nbrlen.c\
		ft_pow.c\
		ft_putarr.c\
		ft_putchar.c\
		ft_putchar_fd.c\
		ft_putstr.c\
		ft_stradd.c\
		ft_straddchar.c\
		ft_strcat.c\
		ft_strchr.c\
		ft_strchrlen.c\
		ft_strcmp.c\
		ft_strcpy.c\
		ft_strcut.c\
		ft_strdel.c\
		ft_strdup.c\
		ft_strendswith.c\
		ft_strequ.c\
		ft_stringsplit.c\
		ft_strjoin.c\
		ft_strjoinf.c\
		ft_strlen.c\
		ft_strncmp.c\
		ft_strncpy.c\
		ft_strndup.c\
		ft_strnequ.c\
		ft_strnew.c\
		ft_strnrev.c\
		ft_strsplit.c\
		ft_strsub.c\
		ft_strtrim.c\
		ft_swap.c\
		ft_wordcount.c\
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
