# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 15:34:25 by mkerrien          #+#    #+#              #
#    Updated: 2025/02/06 03:53:46 by mkerrien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g3

NAME	= fractol 

LIBPATH = -Lmlx_linux -Llibft -L/usr/lib

LIBNAME = -lmlx_Linux -lft -lz -lX11 -lXext -lm

SRC		= ./fractol.c ./main.c ./maths_functions.c ./initialize.c \
		  ./rendering.c ./handle_hooks.c ./strings_utils.c

INCLUDE	= -I/usr/include -Ilibft/includes -Iincludes -Imlx_linux

OBJ		= $(SRC:.c=.o)

all		: MLX LIBFT $(NAME)

LIBFT	:
	@make -C libft >>/dev/null

MLX		:
	@make -C mlx_linux >> /dev/null

$(NAME)	: $(OBJ)
	$(CC) $(CFLAGS) $(SRC) $(LIBPATH) $(INCLUDE) $(LIBNAME) -o $(NAME)

clean	:
	rm -f $(OBJ) ./mlx_linux/*.o ./libft/*.o

fclean	: clean
	rm -f $(NAME) ./mlx_linux/*.a ./libft/*.a

re		: fclean all

.PHONY	: all clean fclean re
