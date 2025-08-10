#include "fractol.h"

/**
 * @brief  Initialize Buddhabrot-specific parameters in the fractal context.
 *
 * Sets up the `t_fractal` structure with initial values for Buddhabrot
 * rendering, including color ranges, iteration limits, sampling parameters,
 * and rendering mode flags. Initializes the MLX connection and screen
 * dimensions, applies fullscreen settings if requested, and prepares
 * general fractal data.
 *
 * @param  argv  Program arguments, used to check for fullscreen mode flag.
 * @param  f     Pointer to the fractal context to configure.
 * @return None.
 *
 * @note   This function does not allocate histograms or start rendering.
 * @pre    `f` must be a valid pointer to a `t_fractal` structure.
 * @post   `f` is populated with default Buddhabrot rendering parameters
 *         and ready for histogram allocation.
 */
static void	buddhabrot_setup_context(char **argv, t_fractal *f)
{
	f->name = "buddhabrot";
	f->mlx_ptr = mlx_init();
	if (!f->mlx_ptr)
		malloc_error();
	print_launch_messages('B');
	is_fullscreen(argv, f);
	mlx_get_screen_size(f->mlx_ptr, &f->img.full_width, &f->img.full_height);
	set_real_screen_size(f);
	data_init(f);
	f->init_color_min = 0x1E3A8A;
	f->init_color_max = 0xF59E0B;
	f->color_min = f->init_color_min;
	f->color_max = f->init_color_max;
	f->max_iterations = 500;
	f->bb_samples_per_tick = 50000;
	f->bb_min_iter = 20;
	f->bb_max_iter = 1000;
	f->bb_nebula = 'N';
	f->bb_seed = (unsigned int)time(NULL);
	f->bb_samples_total = 0;
	f->bb_max_count = 1;
}

/**
 * @brief  Initialize and start the Buddhabrot rendering process.
 *
 * Prepares the fractal context for Buddhabrot rendering by setting up
 * parameters, allocating and resetting histograms, initializing MLX
 * resources, and entering the MLX event loop with a Buddhabrot rendering
 * hook.
 *
 * @param  argv  Program arguments, passed to context setup for fullscreen
 *               mode detection.
 * @param  f     Pointer to the fractal context (`t_fractal`) to initialize.
 * @return None.
 *
 * @note   On allocation failure, calls `malloc_error()` and exits.
 * @pre    `f` must be allocated and ready to be initialized.
 * @post   The Buddhabrot rendering loop runs until the program is closed.
 */
void	init_buddhabrot(char **argv, t_fractal *f)
{
	buddhabrot_setup_context(argv, f);
	if (!bb_alloc_histograms(f))
		malloc_error();
	bb_reset_histograms(f);
	init_mlx(f);
	mlx_loop_hook(f->mlx_ptr, buddhabrot_loop, f);
	mlx_loop(f->mlx_ptr);
}
