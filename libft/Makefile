# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 19:20:24 by mkerrien          #+#    #+#              #
#    Updated: 2025/08/03 21:36:20 by mkerrien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra

NAME		=	libft.a

SRC			=	./ft_isalpha.c \
				./ft_isdigit.c \
				./ft_isalnum.c \
				./ft_isascii.c \
				./ft_isprint.c \
				./ft_strlen.c \
				./ft_memset.c \
				./ft_bzero.c \
				./ft_memcpy.c \
				./ft_memmove.c \
				./ft_strcpy.c \
				./ft_strlcpy.c \
				./ft_strlcat.c \
				./ft_first_l_in_up.c \
				./ft_toupper.c \
				./ft_tolower.c \
				./ft_str_toupper.c \
				./ft_str_tolower.c \
				./ft_strchr.c \
				./ft_strrchr.c \
				./ft_strcmp.c \
				./ft_strcmp_safe.c \
				./ft_strncmp.c \
				./ft_strncmp_safe.c \
				./ft_memchr.c \
				./ft_memcmp.c \
				./ft_strnstr.c \
				./ft_atoi.c \
				./ft_atod.c \
				./ft_calloc.c \
				./ft_fcalloc.c \
				./ft_strdup.c \
				./ft_strsdup.c \
				./ft_free_fullstrs.c \
				./ft_free_strs.c \
				./ft_substr.c \
				./ft_strjoin.c \
				./ft_strfjoin.c \
				./ft_strtrim.c \
				./ft_split.c \
				./ft_itoa.c \
				./ft_ltoa.c \
				./ft_dtoa.c \
				./ft_strmapi.c \
				./ft_striteri.c \
				./ft_putchar.c \
				./ft_putchar_fd.c \
				./ft_putstr.c \
				./ft_putstr_fd.c \
				./ft_putendl_fd.c \
				./ft_putnbr.c \
				./ft_putnbr_fd.c \
				./ft_putunbr.c \
				./ft_putunbr_fd.c \
				./ft_puthex.c \
				./ft_puthex_fd.c \
				./ft_putptr.c \
				./ft_putptr_fd.c \
				./ft_printf.c \
				./ft_printf_fd.c \
				./get_next_line.c \
				./ft_check_int_overflow.c \
				./ft_lstnew_bonus.c \
				./ft_lstadd_front_bonus.c \
				./ft_lstsize_bonus.c \
				./ft_lstlast_bonus.c \
				./ft_lstadd_back_bonus.c \
				./ft_lstdelone_bonus.c \
				./ft_lstclear_bonus.c \
				./ft_lstiter_bonus.c \
				./ft_lstmap_bonus.c \
				./ft_lstmap_bonus.c

OBJ			= $(SRC:.c=.o)

.PHONY		: all
all			: $(NAME)

$(NAME)		: $(OBJ)
	@echo "Compiling the libft..."
	ar rcs $(NAME) $(OBJ)
	@echo "\nLibft compiled !\n"

.PHONY		: clean
clean		:
	@rm -f $(OBJ)

.PHONY		: fclean
fclean		: clean
	@rm -f $(NAME)
	@echo "Libft cleaned !"

.PHONY		: re
re			: fclean all

.PHONY		: listC
listC:
	@find -wholename "./srcs/*.c" | cut -c 3- | tr '\n' ' ';

.PHONY		: listNb
listNb:
	@find -wholename "./srcs/*.c" | wc -l
