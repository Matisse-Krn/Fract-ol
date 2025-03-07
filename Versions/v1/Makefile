# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 15:34:25 by mkerrien          #+#    #+#              #
#    Updated: 2025/02/07 23:19:52 by mkerrien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3
NAME			= fractol 

LIBPATH 		= -Lmlx_linux -Llibft -L/usr/lib
LIBNAME 		= -lmlx_Linux -lft -lz -lX11 -lXext -lm

SRC				= ./fractol.c ./maths_functions.c ./rendering.c ./main.c \
				./handle_hooks.c ./strings_utils.c ./text_box.c \
				./strings_utils2.c ./manipulate_colors.c ./display_functions.c \
				./change_colors.c ./initialize.c ./handle_hooks2.c \
				./parsing.c ./sierpinski_bonus.c ./sierpinski_utils_bonus.c

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

.PHONY			: all bonus clean fclean re bonus
