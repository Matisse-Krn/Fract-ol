#include "fractol.h"

/*
 * Determines the color of a pixel based on the number of iterations before
	escaping the fractal boundary.
 * Uses either smooth color interpolation or psychedelic mode scaling.
 * 
 * @param z A pointer to the complex number at the current pixel.
 * @param pixel A pointer to the pixel structure containing coordinates and
		iteration count.
 * @param fractal A pointer to the fractal structure.
 * @return Returns 1 if the pixel is colored, 0 otherwise.
*/
static int	distrib_colors(t_complex *z, t_pixel *pixel, t_fractal *fractal)
{
	if ((z->real * z->real) + (z->imag * z->imag) > fractal->escape_value)
	{
		if (fractal->psy == 'N')
		{
			fractal->color = interpolate_color(fractal->color_min,
					fractal->color_max, pixel->i, fractal);
		}
		else if (fractal->psy == 'Y')
		{
			fractal->color = scale_map(pixel->i, fractal->color_min,
					fractal->color_max, fractal->max_iterations);
		}
		my_mlx_pixel_put(&fractal->img, pixel->x, pixel->y, fractal->color);
		return (1);
	}
	return (0);
}

/*
 * Computes the color of a pixel for the Mandelbrot set.
 * Iterates through the escape-time algorithm until divergence is detected
	or the maximum number of iterations is reached.
 *
 * Apply an iterative algorithm to determine whether the complex point
	corresponding to (x, y) belongs to the fractal
 * The calculation follows the following recurrence : `z(n+1) = z(n)² + c`
	where :
	- 'z' is initialized to (0,0) ;
	- 'c' is obtained by mapping (x, y) in the complex plane
 * At each iteration:
	- If |z|² exceeds 'escape_value', the pixel is colored according
		to the number of iterations before divergence.
	- If the loop reaches 'max_iterations' without diverging,
		the pixel is colored black (='0x000000')
 * 
 * @param pixel A pointer to the pixel structure containing coordinates.
 * @param fractal A pointer to the fractal structure.
*/
void	handle_pixel_mandelbrot(t_pixel *pixel, t_fractal *fractal)
{
	t_complex	z;
	t_complex	z_squared;
	t_complex	c;

	z.real = 0;
	z.imag = 0;
	c.real = scale_map(pixel->x, -fractal->zoom_rate, fractal->zoom_rate,
			fractal->img.width) + fractal->shift_x;
	c.imag = scale_map(pixel->y, fractal->zoom_rate, -fractal->zoom_rate,
			fractal->img.height) + fractal->shift_y;
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

/*
 * Computes the color of a pixel for the Julia set.
 * Iterates through the escape-time algorithm until divergence is detected
	or the maximum number of iterations is reached.
 *
 * Applies an iterative algorithm to determine whether the complex point
	corresponding to (x, y) belongs to the fractal.
 * The calculation follows the following recurrence : `z(n+1) = z(n)² + c`
	where :
	- 'z' is initialized using the mapped coordinates of (x, y) 
		in the complex plane.
	- 'c' is a constant complex number, specific to each Julia set,
		defined by the user at program launch.
 * At each iteration:
	- If |z|² exceeds 'escape_value', the pixel is colored according
		to the number of iterations before divergence.
	- If the loop reaches 'max_iterations' without diverging,
		the pixel is colored black (='0x000000')
 * 
 * @param pixel A pointer to the pixel structure containing coordinates.
 * @param fractal A pointer to the fractal structure.
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

/*
 * Iterates over all pixels in the image and applies the appropriate fractal
	algorithm (Mandelbrot or Julia) to determine the pixel colors.
 * 
 * @param type The fractal type ('M' for Mandelbrot, 'J' for Julia).
 * @param fractal A pointer to the fractal structure.
*/
static void	pixel_loop(char type, t_fractal *fractal)
{
	t_pixel	pixel;

	pixel.y = -1;
	if (type == 'M')
	{
		ft_putstr_fd("Rendering Mandelbrot...\n\n", 1);
		while (++(pixel.y) <= fractal->img.height)
		{
			pixel.x = -1;
			while (++(pixel.x) <= fractal->img.width)
				handle_pixel_mandelbrot(&pixel, fractal);
		}
	}
	else if (type == 'J')
	{
		ft_putstr_fd("Rendering Julia...\n\n", 1);
		while (++(pixel.y) <= fractal->img.height)
		{
			pixel.x = -1;
			while (++(pixel.x) <= fractal->img.width)
				handle_pixel_julia(&pixel, fractal);
		}
	}
}

/*
 * Initiates the rendering process for the selected fractal type.
 * Calls pixel_loop() to compute pixel colors and updates the window display.
 * 
 * Based on the fractal name stored in the structure, determines
	whether to render a Mandelbrot set or a Julia set.
 * Calls pixel_loop() with the appropriate type ('M' or 'J'),
	which iterates over every pixel of the image and assigns it a color
	according to the escape-time algorithm.
 * Once the entire image has been computed, the function updates
	the MiniLibX window with the new fractal representation.
 * Finally, calls manage_text() to update any text overlays.
 * 
 * @param fractal A pointer to the fractal structure.
*/
void	fractal_rendering(t_fractal *fractal)
{
	if (fractal->multithread == FALSE)
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
