#
# https://github.com/Epicurius
# 
# Created: 2022/01/16 14:04:15 Niklas Neronin
# Updated: 2022/01/22 11:51:47 Niklas Neronin
#

RED		:= "\e[0;31m"
GREEN	:= "\e[0;32m"
YELLOW	:= "\e[0;33m"
BLUE	:= "\e[0;34m"
MAGENTA	:= "\e[0;35m"
CYAN	:= "\e[0;36m"
RESET	:= "\e[0m"

RAW	=	read_bmp.c \
		read_bxpm.c \
		pix_to_bmp.c \
		pix_to_bxpm.c \
		bmp_to_bxpm.c \
		write_bmp.c \
		write_bxpm.c \
		write_bxpm2.c \
		byte_utils.c \
		read_bxpm_scaled.c \
		free.c
 
NAME = libbxpm.a
CDIR = srcs
IDIR = -I. -I ../libft -I ../libpf
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
