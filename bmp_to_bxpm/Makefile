# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/25 13:39:16 by nneronin          #+#    #+#              #
#    Updated: 2021/04/30 14:27:52 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = converter

SRC =	converter.c\
		read_byte.c\
		create_bxpm.c\
		write_bbmp.c\
		write_bxpm.c\

OBJ = $(SRCS:.c=.o)

INCLUDES = ../lib/libft/libft.a ../lib/libpf/libpf.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRC)
	@gcc -o $(NAME) $(SRC) $(INCLUDES)
	@echo "$(NAME) was created."

clean:
	/bin/rm -f $(OBJ)
fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean
