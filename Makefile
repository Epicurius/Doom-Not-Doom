# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/26 11:13:50 by nneronin          #+#    #+#              #
#    Updated: 2021/08/25 13:24:41 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL_NAME	:= $(shell uname -s)

all: 
	@echo "OS: $(SHELL_NAME)"
ifeq ($(SHELL_NAME), Darwin)
	@echo "Making mac version."
	@make -f InstallationTools/Makefile-mac
else
	@echo "Making windows version."
	@mingw32-make -f InstallationTools/Makefile-win
endif

clean:
ifeq ($(SHELL_NAME), Darwin)
	@make clean -f InstallationTools/Makefile-mac
else
	@mingw32-make clean -f InstallationTools/Makefile-win 
endif
	
fclean:
ifeq ($(SHELL_NAME), Darwin)
	@make fclean -f InstallationTools/Makefile-mac
else
	@mingw32-make fclean -f InstallationTools/Makefile-win 
endif

re: fclean all

.PHONY: clean, all, re, fclean
