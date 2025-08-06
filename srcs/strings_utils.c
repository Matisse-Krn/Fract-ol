#include "fractol.h"

/*
 * Appends the initial Julia set parameters to the window name.
 * The format includes the real and imaginary parts of the user-defined
	complex number.
 * 
 * @param name A pointer to the string representing the window name.
 * @param fractal A pointer to the fractal structure.
 * 
 * Process:
	- If both `init_c_real` and `init_c_imag` are set, appends them to `name`.
	- Uses str_append() to concatenate values while ensuring memory safety.
	- Adds spacing to maintain readability in the window title.
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

/*
 * Generates a formatted window name based on the fractal type and image size.
 * Appends additional details for the Julia set if parameters are provided.
 * 
 * @param fractal A pointer to the fractal structure.
 * @return A dynamically allocated string representing the window name.
 * 
 * Process:
	- Converts the first letter of the fractal name to uppercase using
		ft_first_l_in_up().
	- If the fractal is Julia, calls get_julia_details() to add
		parameter details.
	- Appends the image width and height to the name.
	- Ensures memory safety using if_malloc_error().
 * 
 * Memory:
	- The caller is responsible for freeing the returned string.
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

/*
 * Displays the maximum number of iterations on the fractal window.
 * Converts `max_iterations` to a string and prints it at a fixed position.
 * 
 * @param fractal A pointer to the fractal structure.
 * 
 * Memory:
	- The allocated string for `max_iterations` is freed after usage.
*/
void	put_max_iterations(t_fractal *fractal)
{
	char	*max_iterations;

	max_iterations = ft_itoa(fractal->max_iterations);
	put_a_string(5, 10, "Max iterations : ", fractal);
	put_a_string(105, 10, max_iterations, fractal);
	free (max_iterations);
}

/*
 * Displays the current color mode and psychedelic mode status on the
	fractal window.
 * 
 * @param fractal A pointer to the fractal structure.
 * 
 * Display:
	- Prints "Color :" followed by the active color mode.
	- Prints "Range color mode :" followed by the active range color mode (PSYCHEDELIC, COMPLEMENTARY, NORMAL),
	- Uses put_a_string() for rendering text.
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
		put_a_string(120, 40, "Range color mode : PSYCHEDELIC", fractal);
	else if (fractal->range_color_mode == 'N')
		put_a_string(120, 40, "Range color mode : NORMAL", fractal);
	else if (fractal->range_color_mode == 'C')
		put_a_string(120, 40, "Range color mode : COMPLEMENTARY", fractal);

}
