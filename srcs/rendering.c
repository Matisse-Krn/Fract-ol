#include "fractol.h"

/**
 * @brief  Determines pixel color based on escape condition.
 *
 * Checks if the current complex point `z` has escaped the fractal's boundary
 * (using `escape_value`). If escaped, assigns the appropriate color depending
 * on the current color mode (normal or psychedelic) and plots it in the image.
 * If not escaped, no drawing occurs here.
 *
 * @param  z       Pointer to the complex number being iterated.
 * @param  pixel   Pointer to the pixel data (coordinates and iteration count).
 * @param  f       Pointer to the fractal context containing settings and image.
 * @return Returns 1 if the point has escaped and was colored, 0 otherwise.
 *
 * @note   Color mapping depends on `range_color_mode` ('N' for normal,
 *         'Y' for psychedelic gradient mode).
 * @pre    `pixel->i` must contain the current iteration count.
 * @post   If escaped, the pixel is drawn in the output image.
 */
int	distrib_colors(t_complex *z, t_pixel *pixel, t_fractal *f)
{
	if ((z->real * z->real) + (z->imag * z->imag) > f->escape_value)
	{
		if (f->range_color_mode == 'N')
			f->color = interpolate_color(f->color_min,
					f->color_max, pixel->i, f);
		else if (f->range_color_mode == 'Y')
			f->color = scale_map(pixel->i, f->color_min,
					f->color_max, f->max_iterations);
		my_mlx_pixel_put(&f->img, pixel->x, pixel->y, f->color);
		return (1);
	}
	return (0);
}

/**
 * @brief  Processes and colors a single Mandelbrot pixel.
 *
 * Iterates the Mandelbrot formula z = z² + c starting from z = 0,
 * mapping the pixel coordinates to the complex plane based on the
 * current zoom and position. If the escape condition is met, the pixel
 * is colored; otherwise, it is set to black.
 *
 * @param  pixel     Pointer to the pixel structure
 *					 (coordinates, iteration count).
 * @param  fractal   Pointer to the fractal context with rendering parameters.
 * @return None.
 *
 * @note   The escape condition is handled by `distrib_colors()`.
 * @pre    `fractal` must be initialized with valid zoom, shift, and image size.
 * @post   The corresponding pixel in the image is updated with its final color.
 */

void	handle_pixel_mandelbrot(t_pixel *pixel, t_fractal *fractal)
{
	t_complex	z;
	t_complex	z_squared;
	t_complex	c;
	double		x_range;

	z.real = 0;
	z.imag = 0;
	x_range = (1.6 / fractal->zoom_rate) * fractal->aspect_ratio;
	c.real = scale_map(pixel->x, -x_range, x_range,
			fractal->img.width) + fractal->shift_x;
	c.imag = scale_map(pixel->y, 1.6 / fractal->zoom_rate, -1.6
			/ fractal->zoom_rate, fractal->img.height) + fractal->shift_y;
	pixel->i = -1;
	while (++(pixel->i) < fractal->max_iterations)
	{
		z_squared = square_complex(z);
		z = sum_complex(z_squared, c);
		if (distrib_colors(&z, pixel, fractal))
			return ;
	}
	my_mlx_pixel_put(&fractal->img, pixel->x, pixel->y, 0x000000);
}

/**
 * @brief  Processes and colors a single Julia pixel.
 *
 * Iterates the Julia formula z = z² + c, where `c` is fixed and defined
 * by the fractal context or preset. The initial z value is determined
 * from the pixel's position on the screen, mapped to the complex plane.
 * The pixel is colored if the escape condition is met; otherwise, it is black.
 *
 * @param  pixel     Pointer to the pixel structure
 *					 (coordinates, iteration count).
 * @param  fractal   Pointer to the fractal context with rendering parameters.
 * @return None.
 *
 * @note   The escape condition is handled by `distrib_colors()`.
 * @pre    `fractal->c` must be set to the Julia constant.
 * @post   The corresponding pixel in the image is updated with its final color.
 */
void	handle_pixel_julia(t_pixel *pixel, t_fractal *fractal)
{
	t_complex	z;
	t_complex	z_squared;
	t_complex	c;

	z = julia_init_complex(pixel, fractal);
	c = fractal->c;
	pixel->i = -1;
	while (++(pixel->i) < fractal->max_iterations)
	{
		z_squared = square_complex(z);
		z = sum_complex(z_squared, c);
		if (distrib_colors(&z, pixel, fractal))
			return ;
	}
	my_mlx_pixel_put(&fractal->img, pixel->x, pixel->y, 0x000000);
}

/**
 * @brief  Renders a full fractal frame sequentially (single-threaded).
 *
 * Loops over all pixels in the image and processes them either as part
 * of a Mandelbrot or Julia set, depending on the `type` parameter.
 * Uses `handle_pixel_mandelbrot()` or `handle_pixel_julia()` for
 * pixel processing.
 *
 * @param  type      'M' for Mandelbrot, 'J' for Julia.
 * @param  fractal   Pointer to the fractal context containing
 *					 rendering parameters.
 * @return None.
 *
 * @note   This function is only used in single-threaded mode.
 * @pre    The fractal image buffer must be allocated and initialized.
 * @post   The image buffer is fully updated with the rendered fractal.
 */
void	pixel_loop(char type, t_fractal *fractal)
{
	t_pixel	pixel;

	pixel.y = -1;
	if (type == 'M')
	{
		ft_putstr_fd("Rendering Mandelbrot...\n\n", 1);
		while (++(pixel.y) < fractal->img.height)
		{
			pixel.x = -1;
			while (++(pixel.x) < fractal->img.width)
				handle_pixel_mandelbrot(&pixel, fractal);
		}
	}
	else if (type == 'J')
	{
		ft_putstr_fd("Rendering Julia...\n\n", 1);
		while (++(pixel.y) < fractal->img.height)
		{
			pixel.x = -1;
			while (++(pixel.x) < fractal->img.width)
				handle_pixel_julia(&pixel, fractal);
		}
	}
}

/**
 * @brief  Main fractal rendering dispatcher.
 *
 * Determines the appropriate rendering method (single-threaded or
 * multi-threaded) and rendering mode. Handles special modes such as
 * adaptive coloring, and delegates the actual pixel processing to the
 * relevant functions. Once the image is computed, it is displayed
 * in the window and overlay text is drawn.
 *
 * @param  fractal  Pointer to the fractal context containing all parameters.
 * @return None.
 *
 * @note   Multi-threaded rendering uses `init_threads()` for
 *		   parallel processing.
 * @warning Rendering performance may vary greatly depending on resolution,
 *          fractal complexity, and zoom level.
 * @pre    `fractal` must be fully initialized with image buffers and MLX window.
 * @post   The window displays the newly rendered fractal image with overlays.
 */
void	fractal_rendering(t_fractal *fractal)
{
	if (fractal->render_mode == 'A')
	{
		if (fractal->mt == FALSE)
			find_imax_frame(ft_toupper(*fractal->name), fractal);
		else
		{
			if (find_imax_frame_mt(fractal) == FALSE)
				return ;
		}
	}
	if (fractal->mt == FALSE)
	{
		if (!ft_strcmp(fractal->name, "mandelbrot"))
			pixel_loop('M', fractal);
		else if (!ft_strcmp(fractal->name, "julia"))
			pixel_loop('J', fractal);
	}
	else
	{
		if (init_threads(fractal) == FALSE)
			return ;
	}
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr,
		fractal->img.img_ptr, 0, 0);
	manage_text(fractal);
}
