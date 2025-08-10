#include "fractol.h"

/**
 * @brief  Initialize the MiniLibX environment for fractal rendering.
 *
 * Sets up the application window, image buffer, and event handling
 * by calling the respective initialization functions.
 *
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   This function must be called before entering the main event loop.
 * @pre    `fractal` must be allocated and partially initialized.
 * @post   The MLX window, image, and events are ready for rendering.
 */
void	init_mlx(t_fractal *fractal)
{
	initialize_window(fractal);
	initialize_image(fractal);
	initialize_events(fractal);
}

/**
 * @brief  Display an error message for an invalid Sierpinski depth value.
 *
 * Prints a warning when the provided depth value is outside the
 * allowed range for the current window size, and shows the value
 * that will be applied instead.
 *
 * @param  argv     Command-line arguments array
 *					(used to read the invalid value).
 * @param  fractal  Pointer to the fractal context (`t_fractal`) containing
 *                  the maximum allowed depth and the applied depth.
 * @return None.
 *
 * @note   This is a non-blocking error; execution continues after printing.
 * @pre    `argv` and `fractal` must be valid pointers.
 * @post   An error message is printed to stdout.
 */
void	invalid_depth(char **argv, t_fractal *fractal)
{
	ft_printf("%s is an invalid depth value for Sierpinski Carpet...\n\
Allowed values in a window of this size : [0-%d]\nValue applied to \
depth : %d\n", argv[2], fractal->max_depth, fractal->depth);
}

/**
 * @brief  Print a launch message identifying the selected fractal type.
 *
 * Displays a short message with an icon corresponding to the selected fractal:
 * - 'M' → Mandelbrot
 * - 'J' → Julia
 * - 'S' → Sierpinski Carpet
 * - 'B' → Buddhabrot
 *
 * @param  type  Character identifying the fractal type.
 * @return None.
 *
 * @note   Messages are printed to stdout.
 * @pre    `type` must be one of the supported identifiers.
 * @post   A launch message is displayed in the terminal.
 */
void	print_launch_messages(char type)
{
	if (type == 'M')
	{
		ft_putstr_fd("🦠 Mandelbrot fractal identified ! 🦠\n", 1);
		ft_putstr_fd("\t⚙️  Launching the program... ⚙️\n", 1);
	}
	else if (type == 'J')
	{
		ft_putstr_fd("🦠 Julia fractal identified ! 🦠\n", 1);
		ft_putstr_fd("\t⚙️  Launching the program... ⚙️ \n", 1);
	}
	else if (type == 'S')
	{
		ft_putstr_fd("🧊 Sierpinski fractal identified ! 🧊\n", 1);
		ft_putstr_fd("\t⚙️  Launching the program... ⚙️ \n", 1);
	}
	else if (type == 'B')
	{
		ft_putstr_fd("🧘 Buddhabrot identified ! 🧘\n", 1);
		ft_putstr_fd("\t⚙️  Launching the program... ⚙️ \n", 1);
	}
}

/**
 * @brief  Check if fullscreen mode is requested via command-line arguments.
 *
 * Scans the program arguments for the "-f" option and updates the
 * `fullscreen` flag in the fractal context accordingly.
 *
 * @param  argv     Command-line arguments array.
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   If "-f" is found, `fullscreen` is set to TRUE; otherwise FALSE.
 * @pre    `argv` and `fractal` must be valid pointers.
 * @post   The `fullscreen` field of `fractal` is updated.
 */

void	is_fullscreen(char **argv, t_fractal *fractal)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (!ft_strncmp(argv[i], "-f", 2))
		{
			fractal->fullscreen = TRUE;
			return ;
		}
	}
	fractal->fullscreen = FALSE;
}

/**
 * @brief  Configure multi-threading based on command-line arguments.
 *
 * Enables multi-threading by default, but disables it if "-mt=no"
 * is found in the arguments or if the fractal type is "sierpinski".
 *
 * @param  argv     Command-line arguments array.
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   Multi-threading is disabled for Sierpinski fractals by default.
 * @pre    `argv` and `fractal` must be valid pointers.
 * @post   The `mt` (multi-threading) field of `fractal` is updated.
 */
void	set_multi_threading(char **argv, t_fractal *fractal)
{
	int	i;

	i = -1;
	fractal->mt = TRUE;
	while (argv[++i])
	{
		if (!ft_strncmp(argv[i], "-mt=no", 6)
			|| !ft_strcmp("sierpinski", argv[1]))
			fractal->mt = FALSE;
	}
}
