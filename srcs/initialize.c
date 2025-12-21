#include "fractol.h"

/**
 * @brief  Initialize the initial position and zoom for the fractal view.
 *
 * Sets the default shift and zoom values based on the fractal type.
 * Special cases:
 * - Mandelbrot and Buddhabrot are horizontally shifted by -0.6.
 * - Buddhabrot has an initial zoom of 0.5, others default to 1.0.
 * Also initializes the backup values for reset operations and
 * sets default empty strings for complex constants if not provided.
 *
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   Called internally by `data_init()` to configure the initial view.
 * @pre    `fractal->name` must be initialized with the fractal type.
 * @post   Initial position and zoom values are set.
 */
static void	position_init(t_fractal *fractal)
{
	fractal->shift_x = 0;
	if (!ft_strcmp(fractal->name, "mandelbrot")
		|| !ft_strcmp(fractal->name, "buddhabrot"))
		fractal->shift_x = -0.6;
	fractal->shift_y = 0;
	if (!ft_strcmp(fractal->name, "buddhabrot"))
		fractal->zoom_rate = 0.5;
	else
		fractal->zoom_rate = 1;
	fractal->init_shift_x = fractal->shift_x;
	fractal->init_shift_y = fractal->shift_y;
	fractal->init_zoom_rate = fractal->zoom_rate;
	fractal->last_pos = "";
	if (!fractal->init_c_real && !fractal->init_c_imag)
	{
		fractal->init_c_real = "";
		fractal->init_c_imag = "";
	}
}

/**
 * @brief  Initialize all rendering-related data for the fractal.
 *
 * Sets default escape value, iteration limits, color settings,
 * rendering mode, and contrast. Also initializes the position
 * and zoom parameters via `position_init()`.
 *
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   Prints a message indicating whether multi-threading is enabled.
 * @pre    `fractal->mt` must be set before calling.
 * @post   Fractal parameters are ready for rendering.
 */
void	data_init(t_fractal *fractal)
{
	ft_putstr_fd("\t\t💭 Initialize all necessary data... 💭\n", 1);
	if (fractal->mt == TRUE)
		printf("🏁 [MultiThreading=yes] 🏁\n");
	else
		printf("🏁 [MultiThreading=no] 🏁\n");
	fractal->bb_hist = NULL;
	fractal->bb_hist_r = NULL;
	fractal->bb_hist_g = NULL;
	fractal->bb_hist_b = NULL;
	fractal->bb_nebula = 'N';
	fractal->bb_samples_per_tick = 0;
	fractal->bb_min_iter = 0;
	fractal->bb_max_iter = 0;
	fractal->bb_seed = 0;
	fractal->bb_samples_total = 0;
	fractal->bb_max_count = 1;
	fractal->escape_value = pow(2, 2);
	fractal->max_iterations = 200;
	fractal->i_max = 0;
	fractal->tick_iterations = 10;
	fractal->color = 0x000000;
	fractal->init_color_min = 0x000000;
	fractal->init_color_max = 0xFFFFFF;
	fractal->color_min = fractal->init_color_min;
	fractal->color_max = fractal->init_color_max;
	fractal->color_mode = 'N';
	fractal->render_mode = 'N';
	fractal->contrast_exponent = 0.5;
	fractal->range_color_mode = 'N';
	position_init(fractal);
}

/**
 * @brief  Create a new MLX window for the fractal display.
 *
 * Computes the aspect ratio, generates the window title,
 * and creates a new window using MLX. Handles allocation
 * errors by cleaning up resources.
 *
 * @param  f  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   Calls `malloc_error()` and exits if window creation fails.
 * @pre    `f->mlx_ptr` and image dimensions must be initialized.
 * @post   A valid MLX window is created and stored in `f->win_ptr`.
 */
void	initialize_window(t_fractal *f)
{
	char	*name_formatted;

	f->aspect_ratio = (double)f->img.width / (double)f->img.height;
	name_formatted = get_window_name(f);
	if (!name_formatted)
		malloc_error();
	f->win_ptr = mlx_new_window(f->mlx_ptr, f->img.width,
			f->img.height, name_formatted);
	free(name_formatted);
	if (!f->win_ptr)
	{
		mlx_destroy_display(f->mlx_ptr);
		free(f->mlx_ptr);
		malloc_error();
	}
}

/**
 * @brief  Create and prepare the MLX image buffer for fractal rendering.
 *
 * Allocates a new MLX image matching the fractal's dimensions,
 * retrieves the pixel data address, and stores it in the fractal context.
 * Handles allocation errors by cleaning up MLX resources.
 *
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   Calls `malloc_error()` and exits if allocation fails.
 * @pre    `fractal->mlx_ptr` and `fractal->win_ptr` must be valid.
 * @post   The image buffer is ready for pixel drawing.
 */
void	initialize_image(t_fractal *fractal)
{
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_ptr, fractal->img.width,
			fractal->img.height);
	if (!fractal->img.img_ptr)
	{
		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
		mlx_destroy_display(fractal->mlx_ptr);
		free(fractal->mlx_ptr);
		malloc_error();
	}
	fractal->img.px_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bits_per_pixel, &fractal->img.line_length,
			&fractal->img.endian);
	if (!fractal->img.px_ptr)
	{
		mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
		mlx_destroy_display(fractal->mlx_ptr);
		free(fractal->mlx_ptr);
		malloc_error();
	}
	img_lock_init(&fractal->img);
}
