CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3 -O3
NAME			= fractol 

LIBPATH 		= -Lmlx_linux -Llibft -L/usr/lib
LIBNAME 		= -lmlx_Linux -lft -lz -lX11 -lXext -lm

SRC				= srcs/maths_functions.c srcs/rendering.c srcs/errors.c \
				  srcs/main.c srcs/handle_hooks.c srcs/strings_utils.c \
				  srcs/text_box.c srcs/strings_utils2.c srcs/manipulate_colors.c \
				  srcs/display_functions.c srcs/change_colors.c srcs/initialize.c \
				  srcs/handle_hooks2.c srcs/parsing.c srcs/sierpinski_bonus.c \
				  srcs/sierpinski_utils_bonus.c srcs/multithreading.c srcs/init_utils.c \
				  srcs/screen_utils.c srcs/jump_to.c srcs/export_image.c

INCLUDE			= -I/usr/include -Ilibft -Imlx_linux -Iincludes

OBJ				= $(SRC:.c=.o)

all				: $(NAME)

bonus			: $(NAME)

%.o 			: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ >>/dev/null

$(NAME)			: $(OBJ)
	@make -sC libft/ >>/dev/null
	@make -sC mlx_linux/ >>/dev/null
	@$(CC) $(CFLAGS) $(OBJ) $(LIBPATH) $(LIBNAME) $(INCLUDE) -o $(NAME) >>/dev/null
	@echo "\nCompilation done !\n"

clean			:
	@make clean -sC libft/
	rm -rf $(OBJ) $(OBJ_BONUS) ./mlx_linux/obj

fclean			: clean
	@make fclean -sC libft/
	rm -f $(NAME) ./mlx_linux/libmlx.a ./mlx_linux/libmlx_Linux.a

re				: fclean all

.PHONY			: all bonus clean fclean re
