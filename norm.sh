clear
#norminette-beta Makefile Makefile-mac inc
#norminette-beta ./bmp_to_bxpm ../libs/libft ../libs/libbxpm ../libs/libpf ../libs/libtp
norminette-beta srcs > temp_norm
grep Error temp_norm
rm temp_norm
