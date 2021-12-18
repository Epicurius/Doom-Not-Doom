# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/26 11:13:50 by nneronin          #+#    #+#              #
#    Updated: 2021/12/18 12:41:57 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL_NAME	:= $(shell uname -s)

all: 
ifeq ($(SHELL_NAME), Darwin)
	@make -f InstallationTools/Makefile-mac -j6 || :
else
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
