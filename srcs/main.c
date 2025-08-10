#include "fractol.h"

/**
 * @brief  Parses program arguments to initialize the chosen fractal.
 *
 * Determines which fractal type to initialize based on the command-line
 * arguments, and calls the appropriate initialization function for
 * Mandelbrot, Julia, Sierpinski (with or without depth), or Buddhabrot.
 * Also configures multi-threading settings before initialization.
 *
 * @param  argc     The number of command-line arguments.
 * @param  argv     Array of command-line argument strings.
 * @param  fractal  Pointer to the fractal structure to initialize.
 * @return Returns 0 on success (recognized fractal type and initialized),
 *         or 1 if the input is invalid or unrecognized.
 *
 * @note   Ignores `argc` directly via `(void)argc` except for cases where
 *         additional arguments are required (e.g., Julia presets).
 * @warning Providing invalid arguments will prevent initialization and
 *          result in a usage error in the caller.
 * @pre    `argv` must contain at least one valid fractal name at index 1.
 * @post   On success, the fractal structure is configured for rendering.
 */
static int	parse_input(int argc, char **argv, t_fractal *fractal)
{
	set_multi_threading(argv, fractal);
	if (!ft_strcmp(argv[1], "mandelbrot"))
		init_mandelbrot(argv, fractal);
	else if (!ft_strcmp(argv[1], "julia") && argc > 2)
		init_julia(argv, fractal);
	else if (!ft_strcmp(argv[1], "sierpinski") && is_valid_number(argv[2]))
		init_sierpinski_depth(argv, fractal);
	else if (!ft_strcmp(argv[1], "sierpinski"))
		init_sierpinski(argv, fractal);
	else if (!ft_strcmp(argv[1], "buddhabrot"))
		init_buddhabrot(argv, fractal);
	else
		return (1);
	return (0);
}

/**
 * @brief  Program entry point.
 *
 * Handles argument validation, help display, fractal initialization,
 * and starts execution. Exits with an error message if arguments are
 * invalid or insufficient.
 *
 * @param  argc  The number of command-line arguments.
 * @param  argv  Array of command-line argument strings.
 * @return Returns 0 on successful initialization and execution, or 1
 *         on failure (invalid arguments or initialization error).
 *
 * @note   Automatically lowercases the fractal name for easier matching.
 * @warning If `argc < 2`, usage instructions are printed and the program
 *          exits with a non-zero code.
 * @pre    Program must be launched with at least one fractal type name
 *         (e.g., "mandelbrot", "julia", "sierpinski", or "buddhabrot").
 * @post   The specified fractal is initialized; rendering starts if
 *         initialization succeeds.
 */
int	main(int argc, char **argv)
{
	t_fractal	fractal;

	// Benchmark le Buddhabrot afin de trouver le nombre de threads ideal
	if (argc < 2)
		return (usage_error(), 1);
	handle_help(argv);
	ft_bzero(&fractal, sizeof(t_fractal));
	ft_str_tolower(argv[1]);
	if (parse_input(argc, argv, &fractal))
		return (usage_error(), 1);
	return (0);
}
