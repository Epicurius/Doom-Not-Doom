# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/26 11:13:50 by nneronin          #+#    #+#              #
#    Updated: 2022/01/11 15:45:20 by nneronin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL_NAME	:= $(shell uname -s)

#FILES = BuyMenu.wav\
#		AtDoomsGate.wav\
#		Intro.wav
#
#EMBED = $(addprefix resources/WAV/, $(FILES))

all: 
ifeq ($(SHELL_NAME), Darwin)
#	$(foreach file, $(EMBED), xxd -i -p $(file) >> embed.h;)
#	mv embed.h inc/embed.h
	@make -f InstallationTools/Makefile-mac -j6 || :
#	rm inc/embed.h
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
