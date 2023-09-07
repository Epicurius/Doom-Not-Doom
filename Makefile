MAKE		= make
RESOURCES	= resources
MAKE_FLAGS	= -j4 --no-print-directory

LIBS :=  \
	libs/libft \
	libs/libpf \
	libs/libbxpm \
	libs/libtp \
	libs/liblg \
	libs/libui \
	game \
	launcher

all: $(RESOURCES)
	for f in $(LIBS); do \
		$(MAKE) -C $$f $(MAKE_FLAGS) || { exit 1; }; \
	done

clean:
	for f in $(LIBS); do $(MAKE) clean -C $$f $(MAKE_FLAGS); done

fclean:
	for f in $(LIBS); do $(MAKE) fclean -C $$f $(MAKE_FLAGS); done

re: fclean all

$(RESOURCES):
	./DownloadResources.sh || (exit)

# Specify which module to make:
#     'make make-launcher'
make-%:
	$(MAKE) -C $* $(MAKE_FLAGS)

# Print all the steps performed by the specified command. For example:
#	'make test-all'
test-%:
	$(MAKE) --dry-run --always-make $*

.PHONY: clean fclean re
.SILENT:
