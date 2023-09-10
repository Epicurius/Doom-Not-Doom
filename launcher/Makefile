SHELL_NAME	:= $(shell uname -s)

RED		:= "\e[0;31m"
GREEN	:= "\e[0;32m"
YELLOW	:= "\e[0;33m"
BLUE	:= "\e[0;34m"
MAGENTA	:= "\e[0;35m"
CYAN	:= "\e[0;36m"
RESET	:= "\e[0m"

CFILES	= main.c play.c get_root.c settings.c map.c help.c

NAME	=	../launcher
CDIR	=	srcs
ODIR	=	obj
INC		=	-I .
SRCS	=	$(addprefix $(CDIR)/,$(CFILES))
OBJ		=	$(addprefix $(ODIR)/,$(CFILES:.c=.o))
DEP		=	$(OBJ:.o=.d)

LIB_DIR	=	../libs

LIB_INC	=	-I $(LIB_DIR)/libft \
			-I $(LIB_DIR)/libpf \
			-I $(LIB_DIR)/libtp \
			-I $(LIB_DIR)/libbxpm \
			-I $(LIB_DIR)/libui

LIBS	=	-L $(LIB_DIR)/libft -lft \
			-L $(LIB_DIR)/libpf -lpf \
			-L $(LIB_DIR)/libtp -ltp \
			-L $(LIB_DIR)/libbxpm -lbxpm \
			-L $(LIB_DIR)/libui -lui

ifeq ($(SHELL_NAME), Darwin)

LIB_INC	+=	-I SDL2.framework/Headers -I SDL2_ttf.framework/Headers -F ../
LIBS	+=	-framework SDL2 -framework SDL2_ttf -F ../ -rpath @executable_path
CFLAGS	=	-Wall -Wextra -MMD -O3 -flto -Werror -Wfatal-errors #-g -fsanitize=address

else

LIB_INC	+=	-I ../SDL2_includes
LIBS	+=	-L ../ -lSDL2 -lSDL2_ttf
CFLAGS	=	-Wall -Wextra -MMD -Wno-unused-variable -O3 -flto #-Werror -Wfatal-errors

endif

all: $(ODIR) $(NAME)
	@printf $(GREEN)"\e[J[INFO] $(NAME) ready!\n"$(RESET)

-include $(DEP)

$(ODIR):
	@mkdir -p $@

$(NAME): $(OBJ)
	@gcc $(CFLAGS) $(OBJ) $(LIB_INC) $(INC) $(LIBS) -o $(NAME)
	
$(ODIR)/%.o: $(CDIR)/%.c
	@gcc -c $< -o $@ $(CFLAGS) $(LIB_INC) $(INC)
	@printf $(YELLOW)"\e[JCompiling $<\n\e[F"$(RESET)

clean:
	@printf $(CYAN)"[INFO] $(NAME) cleaned!\n"$(RESET)
	@rm -rf $(ODIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean, all, re, fclean