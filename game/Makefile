GREEN	= "\e[0;32m"
YELLOW	= "\e[0;33m"
CYAN	= "\e[0;36m"
RESET	= "\e[0m"

SDIR	= srcs
ODIR	= obj
IDIR	= inc
LDIR	= ../libs

SRCS	:=  $(wildcard $(SDIR)/*.c) \
			$(wildcard $(SDIR)/UI/*.c) \
			$(wildcard $(SDIR)/Init/*.c) \
			$(wildcard $(SDIR)/Math/*.c) \
			$(wildcard $(SDIR)/Free/*.c) \
			$(wildcard $(SDIR)/Draw/*.c) \
			$(wildcard $(SDIR)/Events/*.c) \
			$(wildcard $(SDIR)/BuyMenu/*.c) \
			$(wildcard $(SDIR)/ParseMap/*.c) \
			$(wildcard $(SDIR)/EntityCoords/*.c) \
			$(wildcard $(SDIR)/CollisionDetection/*.c)

INCS	:=	-I ../ \
			-I $(IDIR) \
			-I $(LDIR)/libui \
			-I $(LDIR)/libpf \
			-I $(LDIR)/libft \
			-I $(LDIR)/libtp \
			-I $(LDIR)/libbxpm \
			-I $(LDIR)/liblg

LIBS	:=	-L $(LDIR)/libui -lui \
			-L $(LDIR)/libpf -lpf \
			-L $(LDIR)/libft -lft \
			-L $(LDIR)/libtp -ltp \
			-L $(LDIR)/liblg -llg \
			-L $(LDIR)/libbxpm -lbxpm \
			-L ../ -lSDL2 -lSDL2_ttf -lSDL2_mixer -lm -pthread

NAME	:= doom-game
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
