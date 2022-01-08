clear
#norminette-beta srcs inc ./bmp_to_bxpm ../libs/libft ../libs/libbxpm ../libs/libpf ../libs/libtp > temp_norm
norminette srcs bmp_to_bxpm > temp_norm
grep Error temp_norm
rm temp_norm
