GREEN	:= "\e[0;32m"
YELLOW	:= "\e[0;33m"
CYAN	:= "\e[0;36m"
RESET	:= "\e[0m"

SDIR	= srcs
ODIR	= obj
IDIR	= .

SRCS	:=  $(wildcard $(SDIR)/*.c)

INCS	:=	-I $(IDIR)

NAME	:= libtp.a
OBJS    := $(SRCS:$(SDIR)/%.c=$(ODIR)/%.o)
DEPS	:= $(OBJS:.o=.d)
CFLAGS	:= -Wall -Wextra -Werror -MMD -O3 -Wno-unused-variable

all: $(NAME)
	printf $(GREEN)"\e[J[INFO] $(NAME) ready!\n"$(RESET)

-include $(DEPS)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(ODIR)/%.o: $(SDIR)/%.c
	mkdir -p $(@D)
	gcc -c $< -o $@ $(CFLAGS) $(INCS)
	printf $(YELLOW)"\e[JCompiling $<\n\e[F"$(RESET)

clean:
	printf $(CYAN)"[INFO] $(NAME) cleaned!\n"$(RESET)
	rm -rf $(ODIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean
.SILENT:
