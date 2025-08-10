#include "fractol.h"

/**
 * @brief  Appends Julia set parameters to the window title.
 *
 * If initial Julia parameters (`init_c_real` and `init_c_imag`) are set,
 * this function appends them to the given `name` string, separated by commas
 * and followed by additional spacing. It ensures each allocation succeeds.
 *
 * @param  name      Pointer to the string holding the window title.
 *                   This string will be reallocated and appended to.
 * @param  fractal   Pointer to the fractal context containing Julia parameters.
 * @return None.
 *
 * @note   This function only appends details if both real and imaginary parts
 *         of the Julia constant are non-empty.
 * @warning Terminates the program via `if_malloc_error()` if a memory
 *          allocation fails.
 * @pre    `*name` must be dynamically allocated and modifiable.
 * @post   The `name` string is extended with Julia parameters when applicable.
 */
static void	get_julia_details(char **name, t_fractal *fractal)
{
	if (fractal->init_c_real[0] != '\0' && fractal->init_c_imag[0] != '\0')
	{
		*name = str_append(*name, fractal->init_c_real);
		if_malloc_error(*name);
		*name = str_append(*name, ",  ");
		if_malloc_error(*name);
		*name = str_append(*name, fractal->init_c_imag);
		if_malloc_error(*name);
		*name = str_append(*name, "    ");
		if_malloc_error(*name);
	}
}

/**
 * @brief  Builds the complete window title string.
 *
 * Creates a descriptive window name based on the fractal type, Julia parameters
 * (if applicable), and the current image resolution. Allocates and concatenates
 * each part dynamically.
 *
 * @param  fractal  Pointer to the fractal context containing name, dimensions,
 *                  and Julia parameters.
 * @return Dynamically allocated string containing the window title.
 *
 * @note   The caller is responsible for freeing the returned string.
 * @warning Terminates the program via `if_malloc_error()` if a memory
 *          allocation fails.
 * @pre    The fractal's `name`, `img.width`, and `img.height`
 *		   must be initialized.
 * @post   Returns a newly allocated string containing the full window title.
 */
char	*get_window_name(t_fractal *fractal)
{
	char	*name;
	char	*width;
	char	*height;

	name = ft_first_l_in_up(fractal->name);
	if_malloc_error(name);
	name = str_append(name, "    ");
	if_malloc_error(name);
	get_julia_details(&name, fractal);
	name = str_append(name, " -     ");
	if_malloc_error(name);
	width = ft_itoa(fractal->img.width);
	if_malloc_error(width);
	name = str_append(name, width);
	free(width);
	if_malloc_error(name);
	name = str_append(name, "*");
	if_malloc_error(name);
	height = ft_itoa(fractal->img.height);
	if_malloc_error(height);
	name = str_append(name, height);
	free(height);
	return (if_malloc_error(name));
}

/**
 * @brief  Displays the maximum number of iterations on-screen.
 *
 * Converts the `max_iterations` value to a string and displays it on the window
 * at fixed coordinates using `put_a_string()`.
 *
 * @param  fractal  Pointer to the fractal context containing iteration settings.
 * @return None.
 *
 * @note   The string is freed after being displayed.
 * @pre    The MLX window and image buffer must be initialized.
 * @post   "Max iterations" label and value are rendered to the screen.
 */
void	put_max_iterations(t_fractal *fractal)
{
	char	*max_iterations;

	max_iterations = ft_itoa(fractal->max_iterations);
	put_a_string(5, 10, "Max iterations : ", fractal);
	put_a_string(105, 10, max_iterations, fractal);
	free (max_iterations);
}

/**
 * @brief  Displays the current color mode and psychedelic status.
 *
 * Shows the active color scheme based on `color_mode` and the state of the
 * psychedelic mode (`range_color_mode`). Displays both on the HUD at fixed
 * coordinates.
 *
 * @param  fractal  Pointer to the fractal context containing color settings.
 * @return None.
 *
 * @note   Supported color modes: N (Normal), R (Red), G (Green), B (Blue),
 *         Y (Yellow), O (Orange), P (Pink), C (Cyan).
 * @pre    The MLX window and image buffer must be initialized.
 * @post   Color mode and psychedelic status are rendered to the screen.
 */
void	put_color_mode(t_fractal *fractal)
{
	put_a_string(5, 40, "Color :", fractal);
	if (fractal->color_mode == 'N')
		put_a_string(55, 40, "Normal", fractal);
	else if (fractal->color_mode == 'R')
		put_a_string(55, 40, "Red", fractal);
	else if (fractal->color_mode == 'G')
		put_a_string(55, 40, "Green", fractal);
	else if (fractal->color_mode == 'B')
		put_a_string(55, 40, "Blue", fractal);
	else if (fractal->color_mode == 'Y')
		put_a_string(55, 40, "Yellow", fractal);
	else if (fractal->color_mode == 'O')
		put_a_string(55, 40, "Orange", fractal);
	else if (fractal->color_mode == 'P')
		put_a_string(55, 40, "Pink", fractal);
	else if (fractal->color_mode == 'C')
		put_a_string(55, 40, "Cyan", fractal);
	put_a_string(100, 40, "||", fractal);
	if (fractal->range_color_mode == 'Y')
		put_a_string(120, 40, "Psych. : ON", fractal);
	else if (fractal->range_color_mode == 'N')
		put_a_string(120, 40, "Psych. : OFF", fractal);
}

/**
 * @brief  Displays the current rendering mode on-screen.
 *
 * Renders the name of the active rendering mode (`render_mode`) on the HUD
 * at fixed coordinates using `put_a_string()`.
 *
 * @param  f  Pointer to the fractal context containing the rendering mode.
 * @return None.
 *
 * @note   Supported render modes:
 *         - N: Exponential
 *         - L: Logarithmic
 *         - A: Adaptive
 *         - F: Fixed logarithmic
 *         - C: Cyclic modulo
 * @pre    The MLX window and image buffer must be initialized.
 * @post   Render mode label is displayed on the screen.
 */
void	put_render_mode(t_fractal *f)
{
	put_a_string(5, 55, "Render mode :", f);
	if (f->render_mode == 'N')
		put_a_string(90, 55, "Exponential", f);
	else if (f->render_mode == 'L')
		put_a_string(90, 55, "Logarithmic", f);
	else if (f->render_mode == 'A')
		put_a_string(90, 55, "Adaptive", f);
	else if (f->render_mode == 'F')
		put_a_string(90, 55, "Fixed log.", f);
	else if (f->render_mode == 'C')
		put_a_string(90, 55, "Cyclic modulo", f);
}
