# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/25 13:39:16 by nneronin          #+#    #+#              #
#    Updated: 2021/05/08 14:02:19 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED				:= "\e[0;31m"
GREEN			:= "\e[0;32m"
YELLOW			:= "\e[0;33m"
BLUE			:= "\e[0;34m"
MAGENTA			:= "\e[0;35m"
CYAN			:= "\e[0;36m"
RESET			:= "\e[0m"

NAME = converter

SRC =	converter.c\
		read_byte.c\
		create_bxpm.c\
		write_bxpm.c\
		write_bxpm2.c\

OBJ = $(SRCS:.c=.o)

INCLUDES = ../lib/libft/libft.a ../lib/libpf/libpf.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)
	@printf $(CYAN)"[INFO]	$(NAME) ready!\n"$(RESET)

$(NAME): $(SRC)
	@gcc -o $(NAME) $(SRC) $(INCLUDES)
	@printf $(GREEN)"Compiling $(NAME)\n"$(RESET)

clean:
	/bin/rm -f $(OBJ)
	@printf $(CYAN)"[INFO]	$(NAME) cleaned\n"$(RESET)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean
