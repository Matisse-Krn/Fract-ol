#include "fractol.h"

/**
 * @brief  Initializes and launches the Mandelbrot fractal rendering.
 *
 * Sets up the Mandelbrot fractal environment by initializing MLX, setting
 * display mode (fullscreen or windowed), retrieving screen dimensions,
 * configuring image size, and initializing rendering parameters.
 * Starts the main rendering loop.
 *
 * @param  argv  Command-line arguments array (expects "mandelbrot" as argv[1]).
 * @param  f     Pointer to the fractal rendering context.
 * @return None.
 *
 * @note   This function runs an infinite MLX loop until the window is closed.
 * @warning Exits with an error if MLX initialization fails.
 * @pre    `f` must be a valid pointer; `argv` must
 *		   contain at least two elements.
 * @post   The Mandelbrot fractal is displayed in an interactive window.
 */
void	init_mandelbrot(char **argv, t_fractal *f)
{
	f->name = argv[1];
	f->mlx_ptr = mlx_init();
	if (!f->mlx_ptr)
		malloc_error();
	print_launch_messages('M');
	is_fullscreen(argv, f);
	mlx_get_screen_size(f->mlx_ptr, &f->img.full_width, &f->img.full_height);
	set_real_screen_size(f);
	data_init(f);
	init_mlx(f);
	fractal_rendering(f);
	mlx_loop(f->mlx_ptr);
}

/**
 * @brief  Initializes and launches the Julia fractal rendering.
 *
 * Sets up the Julia fractal environment by initializing MLX, determining
 * display mode, retrieving screen dimensions, assigning initial Julia set
 * parameters (from presets or direct numeric input), and initializing
 * rendering settings. Starts the main rendering loop.
 *
 * @param  argv  Command-line arguments array
 *				 ("julia" as argv[1], plus parameters).
 * @param  f     Pointer to the fractal rendering context.
 * @return None.
 *
 * @note   Supports both preset names and custom coordinates for Julia constants.
 * @warning Exits with an error if MLX initialization fails.
 * @pre    `f` must be a valid pointer; `argv` must
 *		   contain valid Julia parameters.
 * @post   The Julia fractal is displayed interactively.
 */
void	init_julia(char **argv, t_fractal *f)
{
	f->name = argv[1];
	f->mlx_ptr = mlx_init();
	if (!f->mlx_ptr)
		malloc_error();
	print_launch_messages('J');
	is_fullscreen(argv, f);
	mlx_get_screen_size(f->mlx_ptr, &f->img.full_width, &f->img.full_height);
	set_real_screen_size(f);
	assign_params(argv, f);
	data_init(f);
	init_mlx(f);
	fractal_rendering(f);
	mlx_loop(f->mlx_ptr);
}

/**
 * @brief  Initializes and launches the Sierpinski Carpet render (default depth).
 *
 * Sets up the Sierpinski Carpet fractal environment with MLX, retrieves
 * display settings, calculates maximum allowed depth for current resolution,
 * and initializes rendering parameters. Renders the fractal with default depth.
 *
 * @param  argv  Command-line arguments array ("sierpinski" as argv[1]).
 * @param  f     Pointer to the fractal rendering context.
 * @return None.
 *
 * @note   The maximum depth depends on the window size; printed at launch.
 * @warning Exits with an error if MLX initialization fails.
 * @pre    `f` must be valid; `argv` must specify "sierpinski".
 * @post   The Sierpinski Carpet is rendered interactively.
 */
void	init_sierpinski(char **argv, t_fractal *f)
{
	f->name = argv[1];
	f->mlx_ptr = mlx_init();
	if (!f->mlx_ptr)
		malloc_error();
	print_launch_messages('S');
	is_fullscreen(argv, f);
	mlx_get_screen_size(f->mlx_ptr, &f->img.full_width, &f->img.full_height);
	set_real_screen_size(f);
	data_init(f);
	data_init_sierpinski(f);
	ft_printf("🗔  Max depth : %d 🗔\n🕳️  Default depth : %d 🕳️\n",
		f->max_depth, f->depth);
	init_mlx(f);
	rendering_sierpinski(f);
	mlx_loop(f->mlx_ptr);
}

/**
 * @brief  Initializes and launches the Sierpinski Carpet with a specified depth.
 *
 * Similar to `init_sierpinski()` but allows the user to specify the recursion
 * depth via the third command-line argument. Validates the given depth and
 * applies it if within the allowed range.
 *
 * @param  argv  Command-line arguments array ("sierpinski" as argv[1],
 *               desired depth as argv[2]).
 * @param  f     Pointer to the fractal rendering context.
 * @return None.
 *
 * @note   Depth must be a single digit when `max_depth <= 9`.
 * @warning If the depth is invalid, defaults to a safe value and warns the user.
 * @pre    `f` must be valid; `argv` must contain a valid depth parameter.
 * @post   The Sierpinski Carpet is rendered with the specified depth.
 */
void	init_sierpinski_depth(char **argv, t_fractal *f)
{
	f->name = argv[1];
	is_fullscreen(argv, f);
	data_init(f);
	f->mlx_ptr = mlx_init();
	if (!f->mlx_ptr)
		malloc_error();
	mlx_get_screen_size(f->mlx_ptr, &f->img.full_width, &f->img.full_height);
	set_real_screen_size(f);
	print_launch_messages('S');
	data_init_sierpinski(f);
	printf("Max depth = %d\n", f->max_depth);
	if (ft_strlen(argv[2]) == 1 && *argv[2] >= '0' && *argv[2] <= \
		f->max_depth + '0' && f->max_depth <= 9)
	{
		f->depth = ft_atoi(argv[2]);
		ft_printf("🗔  Max depth : %d 🗔\n🕳️  Choosen depth : %d 🕳️\n",
			f->max_depth, f->depth);
	}
	else
		invalid_depth(argv, f);
	init_mlx(f);
	rendering_sierpinski(f);
	mlx_loop(f->mlx_ptr);
}
