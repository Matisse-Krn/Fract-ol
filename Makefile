CC				= cc
CFLAGS			= -g3 -O3 -Wall -Wextra -Werror
NAME			= fractol 

LIBPATH 		= -Lmlx_linux -Llibft -L/usr/lib
LIBNAME 		= -lmlx_Linux -lft -lz -lX11 -lXext -lm

SRC				= srcs/buddhabrot_export_utils.c srcs/errors.c srcs/handle_key_julia_mandelbrot.c srcs/buddhabrot.c srcs/buddhabrot_init.c srcs/change_colors.c srcs/buddhabrot_mutex.c srcs/buddhabrot_mt_ctx.c srcs/help2.c srcs/initialize.c srcs/parsing.c srcs/strings_utils2.c srcs/help.c srcs/export_view_png.c srcs/buddhabrot_histogram.c srcs/adaptive_mode_multithreading.c srcs/rendering.c srcs/stb_image_write_impl.c srcs/manipulate_colors.c srcs/maths_functions.c srcs/buddhabrot_export_view.c srcs/buddhabrot_histogram_mem.c srcs/buddhabrot_mt_sampling_core.c srcs/hud_shortcuts.c srcs/buddhabrot_mt_thread.c srcs/strings_utils.c srcs/julia_presets.c srcs/export_snapshot.c srcs/buddhabrot_draw.c srcs/buddhabrot_mt_hist_local.c srcs/init_utils.c srcs/sierpinski_bonus.c srcs/render_colors_mode.c srcs/buddhabrot_sampling.c srcs/julia_presets_handler2.c srcs/buddhabrot_color.c srcs/jump_to.c srcs/screen_utils.c srcs/buddhabrot_palette_utils.c srcs/buddhabrot_mt_sampling_runner.c srcs/adaptive_mode.c srcs/sierpinski_utils_bonus.c srcs/handle_key_sierpinski_buddhabrot.c srcs/hud_manage_text.c srcs/multithreading.c srcs/text_box.c srcs/julia_presets_handler1.c srcs/initialize_events.c srcs/main.c srcs/handle_mouse_and_exit.c srcs/export_utils.c srcs/export_image.c srcs/buddhabrot_mt_orchestrator.c srcs/display_functions.c

INCLUDE			= -I/usr/include -Ilibft -Imlx_linux -Iincludes

OBJ				= $(SRC:.c=.o)

all				: $(NAME)

bonus			: $(NAME)

%.o 			: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ >>/dev/null

$(NAME)			: $(OBJ) includes/fractol.h
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

listC			:
	@LIST=$$(find -wholename "./srcs/*.c" | cut -c 3- | tr '\n' ' '); \
	printf "🗅 $(INFOS)All C sources files copied into clipboard :\n$(RESET)$$LIST\n"; \
	echo -n $$LIST | xclip -selection clipboard

listNb			:
	@echo "Number of .c files :" 
	@find -wholename "./srcs/*.c" | wc -l

.PHONY			: all bonus clean fclean re listC listNb
