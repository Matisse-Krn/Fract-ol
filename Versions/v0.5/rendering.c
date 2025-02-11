/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:32:51 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/08 02:10:57 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

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
	* Calculates and displays the color of a pixel in a fractal set

	* @x :		  Horizontal coordinate of the pixel to be processed
	* @y :		  Vertical coordinate of the pixel to be processed
	* @fractal :  Pointer to the structure containing the fractal parameters
	
	* Apply an iterative algorithm to determine whether the complex point
	  corresponding to (x, y) belongs to the fractal
	* The calculation follows the following recurrence : `z(n+1) = z(n)² + c`
	  where :
		- 'z' is initialized to (0,0) ;
		- 'c' is obtained by mapping (x, y) in the complex plane
	* At each iteration:
		- If |Z|² exceeds 'escape_value', the pixel is colored according
		  to the number of iterations before divergence.
			* Color is determined by a linear mapping of iteration index 'i'
			  to a range of colors
		- If the loop reaches 'max_iterations' without diverging,
		  the pixel is colored black (='0x000000')
*/
static void	handle_pixel_mandelbrot(t_pixel *pixel, t_fractal *fractal)
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

static t_complex	julia_init_complex(t_pixel *pixel, t_fractal *fractal)
{
	t_complex	z;

	z.real = scale_map(pixel->x, -fractal->zoom_rate, fractal->zoom_rate,
			fractal->img.width) + fractal->shift_x;
	z.imag = scale_map(pixel->y, fractal->zoom_rate, -fractal->zoom_rate,
			fractal->img.height) + fractal->shift_y;
	return (z);
}

static void	handle_pixel_julia(t_pixel *pixel, t_fractal *fractal)
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

void	pixel_loop(char type, t_fractal *fractal)
{
	t_pixel	pixel;

	pixel.y = -1;
	if (type == 'M')
	{
		while (++(pixel.y) <= fractal->img.height)
		{
			pixel.x = -1;
			while (++(pixel.x) <= fractal->img.width)
				handle_pixel_mandelbrot(&pixel, fractal);
		}
		ft_putstr_fd("RENDERING MANDELBROT\n\n", 1);
	}
	else if (type == 'J')
	{
		while (++(pixel.y) <= fractal->img.height)
		{
			pixel.x = -1;
			while (++(pixel.x) <= fractal->img.width)
				handle_pixel_julia(&pixel, fractal);
		}
		ft_putstr_fd("RENDERING JULIA\n\n", 1);
	}
}

/*
	* Apply 'handle_pixel()' to each pixel of the image
	* When done, put the image to window with 'mlx_put_image_to_window()'
	* Then, put some informatives strings onto the window
*/
void	fractal_rendering(t_fractal *fractal)
{
	if (!ft_strcmp(fractal->name, "mandelbrot"))
		pixel_loop('M', fractal);
	else if (!ft_strcmp(fractal->name, "julia"))
		pixel_loop('J', fractal);
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr,
		fractal->img.img_ptr, 0, 0);
	manage_text(fractal);
}
