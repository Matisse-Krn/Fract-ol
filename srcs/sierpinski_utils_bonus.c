#include "fractol.h"

/**
 * @brief  Initializes Sierpinski Carpet parameters based on window size.
 *
 * Validates the window dimensions for rendering the Sierpinski Carpet,
 * determines the maximum drawable size for a square carpet, calculates
 * the maximum recursion depth possible, and sets the initial depth.
 *
 * @param  fractal  Pointer to the fractal context structure.
 * @return None.
 *
 * @note   If the window is smaller than 3x3 pixels, the program exits early
 *         as the carpet cannot be rendered meaningfully.
 * @warning Exits the program if the window size is too small.
 * @pre    The fractal image dimensions (`img.width` and `img.height`) must
 *         be initialized before this call.
 * @post   `fractal->size`, `fractal->max_depth`, and `fractal->depth`
 *         are set appropriately.
 */
void	data_init_sierpinski(t_fractal *fractal)
{
	if (fractal->img.width < 3 || fractal->img.height < 3)
	{
		ft_printf("Window size too small : exit program.\nSee ya' ! 👋\n");
		exit(EXIT_SUCCESS);
	}
	if (fractal->img.width > fractal->img.height)
		fractal->size = fractal->img.height;
	else
		fractal->size = fractal->img.width;
	ft_printf("Sierpinski Carpet size : %d*%d\n", fractal->size, fractal->size);
	fractal->max_depth = get_max_depth(fractal);
	if (!fractal->depth && fractal->max_depth >= 3)
		fractal->depth = 6;
	else if (fractal->max_depth < 3)
		fractal->depth = fractal->max_depth;
}

/**
 * @brief  Calculates the maximum recursion depth for the Sierpinski Carpet.
 *
 * Determines how many times the carpet can be subdivided into thirds
 * based on the smallest window dimension.
 *
 * @param  fractal  Pointer to the fractal context structure.
 * @return Maximum recursion depth as an integer.
 *
 * @note   The calculation uses a base-3 logarithm of the smallest window size.
 * @pre    The fractal image dimensions (`img.width` and `img.height`) must
 *         be initialized before this call.
 * @post   No changes are made to the fractal context.
 */
int	get_max_depth(t_fractal *fractal)
{
	int	min_size;

	if (fractal->img.width < fractal->img.height)
		min_size = fractal->img.width;
	else
		min_size = fractal->img.height;
	return ((int)(log(min_size) / log(3)));
}

/**
 * @brief  Changes the recursion depth of the Sierpinski Carpet.
 *
 * Updates the carpet depth according to a numeric key press, ensuring the
 * new depth does not exceed the maximum allowed or match the current depth.
 * Redraws the carpet with the new depth.
 *
 * @param  keysym   The key symbol representing the chosen depth ('0' to '6').
 * @param  fractal  Pointer to the fractal context structure.
 * @return None.
 *
 * @note   If the chosen depth exceeds the maximum possible depth for the
 *         current window size, no change is applied and a warning is printed.
 * @warning The function destroys and recreates the image buffer before
 *          re-rendering the carpet.
 * @pre    The MLX context and window must be initialized.
 * @post   The carpet is redrawn with the updated recursion depth.
 */
void	change_depth_sierpinski(int keysym, t_fractal *fractal)
{
	if (keysym - '0' > fractal->max_depth || keysym - '0' == fractal->depth)
	{
		if (keysym - '0' > fractal->max_depth)
			ft_printf("Can't increase depth : window size too small !\nDepth \
max : %d\n\n", fractal->max_depth);
		return ;
	}
	ft_printf("Changing depth from [%d->", fractal->depth);
	if ((keysym == XK_0 || keysym == XK_1 || keysym == XK_2 || keysym == XK_3 \
		|| keysym == XK_4 || keysym == XK_5 || keysym == XK_6))
		fractal->depth = keysym - '0';
	ft_printf("%d]\n", fractal->depth);
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	initialize_image(fractal);
	rendering_sierpinski(fractal);
}

/**
 * @brief  Changes the color mode of the Sierpinski Carpet.
 *
 * Updates the color scheme based on a specific key press, allowing the
 * carpet to be displayed in various predefined colors. Redraws the carpet
 * using the new color mode.
 *
 * @param  keysym   The key symbol representing the desired color mode.
 * @param  fractal  Pointer to the fractal context structure.
 * @return None.
 *
 * @note   Supported color modes: 'N' (Normal), 'R' (Red), 'G' (Green),
 *         'B' (Blue), 'Y' (Yellow), 'O' (Orange), 'P' (Purple), 'C' (Cyan).
 * @warning The function destroys and recreates the image buffer before
 *          re-rendering the carpet.
 * @pre    The MLX context and window must be initialized.
 * @post   The carpet is redrawn with the updated color mode.
 */
void	change_color_sierpinski(int keysym, t_fractal *fractal)
{
	if (keysym == XK_n && fractal->color_mode == 'N')
		return ;
	if (keysym == XK_n)
		change_color_mode('N', fractal);
	else if (keysym == XK_r)
		change_color_mode('R', fractal);
	else if (keysym == XK_g)
		change_color_mode('G', fractal);
	else if (keysym == XK_b)
		change_color_mode('B', fractal);
	else if (keysym == XK_y)
		change_color_mode('Y', fractal);
	else if (keysym == XK_o)
		change_color_mode('O', fractal);
	else if (keysym == XK_p)
		change_color_mode('P', fractal);
	else if (keysym == XK_c)
		change_color_mode('C', fractal);
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	initialize_image(fractal);
	rendering_sierpinski(fractal);
}
