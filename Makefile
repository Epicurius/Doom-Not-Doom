SHELL_NAME	= $(shell uname -s)
CPU = $(firstword $(subst -, ,$(shell gcc -dumpmachine)))

MAKE = make

RESOURCES	= resources

all: $(RESOURCES)
	@echo "SYSTEM: "$(SHELL_NAME) "CPU: " $(CPU)
	@$(MAKE) -C ./libs/libft -j6
	@$(MAKE) -C ./libs/libpf -j6
	@$(MAKE) -C ./libs/libbxpm -j6
	@$(MAKE) -C ./libs/libtp -j6
	@$(MAKE) -C ./libs/liblg -j6
	@$(MAKE) -C ./libs/libui -j6 
	@$(MAKE) -C ./game -j6

clean:
	@$(MAKE) clean -C ./libs/libft
	@$(MAKE) clean -C ./libs/libpf
	@$(MAKE) clean -C ./libs/libbxpm
	@$(MAKE) clean -C ./libs/libtp
	@$(MAKE) clean -C ./libs/liblg
	@$(MAKE) clean -C ./libs/libui
	@$(MAKE) clean -C ./game
	
fclean:
	@$(MAKE) fclean -C ./libs/libft
	@$(MAKE) fclean -C ./libs/libpf
	@$(MAKE) fclean -C ./libs/libbxpm
	@$(MAKE) fclean -C ./libs/libtp
	@$(MAKE) fclean -C ./libs/liblg
	@$(MAKE) fclean -C ./libs/libui
	@$(MAKE) fclean -C ./game

re: fclean all

$(RESOURCES):
	@./DownloadResources.sh || (exit)

.PHONY: clean, all, re, fclean
