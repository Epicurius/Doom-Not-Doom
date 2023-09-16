GREEN	:= "\e[0;32m"
YELLOW	:= "\e[0;33m"
CYAN	:= "\e[0;36m"
RESET	:= "\e[0m"

SDIR	= srcs
ODIR	= obj
IDIR	= .
LDIR	= ../libs

SRCS	:=  $(wildcard $(SDIR)/*.c)

INCS	:=	-I ../ \
			-I $(IDIR) \
			-I $(LDIR)/libui \
			-I $(LDIR)/libpf \
			-I $(LDIR)/libft \
			-I $(LDIR)/liblg \
			-I $(LDIR)/libbxpm

LIBS	:=	-L $(LDIR)/libui -lui \
			-L $(LDIR)/libpf -lpf \
			-L $(LDIR)/libft -lft \
			-L $(LDIR)/liblg -llg \
			-L $(LDIR)/libbxpm -lbxpm \
			-L ../ -lSDL2 -lSDL2_ttf -lm

NAME	:= doom-launcher
OBJS    := $(SRCS:$(SDIR)/%.c=$(ODIR)/%.o)
DEPS	:= $(OBJS:.o=.d)
CFLAGS	:= -Wall -Wextra -Werror -MMD -O3 -Wno-unused-variable -Wfatal-errors

all: $(NAME)
	printf $(GREEN)"\e[J[INFO] $(NAME) ready!\n"$(RESET)

-include $(DEPS)

$(NAME): $(OBJS)
	mkdir -p $(@D)
	gcc $(CFLAGS) $(OBJS) $(INCS) $(LIBS) -o ../$(NAME)

$(ODIR)/%.o: $(SDIR)/%.c
	mkdir -p $(@D)
	gcc -c $< -o $@ $(CFLAGS) $(INCS)
	printf $(YELLOW)"\e[JCompiling $<\n\e[F"$(RESET)

clean:
	printf $(CYAN)"[INFO] $(NAME) cleaned!\n"$(RESET)
	rm -rf $(ODIR)

fclean: clean
	rm -f ../$(NAME)

re: fclean all

.PHONY: clean, all, re, fclean
.SILENT:
