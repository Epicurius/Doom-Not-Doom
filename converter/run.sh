gcc -o converter.out converter.c \
	-I ../../libs/libft -L../../libs/libft -lft \
	-I ../../libs/libpf -L../../libs/libpf -lpf \
	-I ../../libs/libbxpm -L../../libs/libbxpm -lbxpm \

./converter.out $@

rm converter.out