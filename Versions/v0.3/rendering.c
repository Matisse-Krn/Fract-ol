/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:32:51 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/04 15:19:23 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

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
static void	handle_pixel_mandelbrot(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	z.real = 0;
	z.imag = 0;
	c.real = scale_map(x, -fractal->zoom_rate, fractal->zoom_rate,
			fractal->img.width) + fractal->shift_x;
	c.imag = scale_map(y, fractal->zoom_rate, -fractal->zoom_rate,
			fractal->img.height) + fractal->shift_y;
	i = 0;
	while (i < fractal->max_iterations)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.real * z.real) + (z.imag * z.imag) > fractal->escape_value)
		{
			color = scale_map(i, 0x000000, 0xFFFFFF, fractal->max_iterations);
			my_mlx_pixel_put(&fractal->img, x, y, color);
			return ;
		}
		i++;
	}
	my_mlx_pixel_put(&fractal->img, x, y, 0x000000);
}

static void	handle_pixel_julia(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	z.real = 0;
	z.imag = 0;
	c.real = scale_map(x, -fractal->zoom_rate, fractal->zoom_rate,
			fractal->img.width) + fractal->shift_x;
	c.imag = scale_map(y, fractal->zoom_rate, -fractal->zoom_rate,
			fractal->img.height) + fractal->shift_y;
	i = 0;
	while (i < fractal->max_iterations)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.real * z.real) + (z.imag * z.imag) > fractal->escape_value)
		{
			color = scale_map(i, 0x000000, 0xFFFFFF, fractal->max_iterations);
			my_mlx_pixel_put(&fractal->img, x, y, color);
			return ;
		}
		i++;
	}
	my_mlx_pixel_put(&fractal->img, x, y, 0x000000);
}

/*
	* Apply 'handle_pixel()' to each pixel of the image
	* When done, put the image to window with 'mlx_put_image_to_window()'
	* Then, put some informatives strings onto the window
*/
void	fractal_rendering(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	if (!ft_strcmp(fractal->name, "mandelbrot"))
	{
		while (++y <= fractal->img.height)
		{
			x = -1;
			while (++x <= fractal->img.width)
				handle_pixel_mandelbrot(x, y, fractal);
		}
	}
	else if (!ft_strcmp(fractal->name, "julia"))
	{
		while (++y <= fractal->img.height)
		{
			x = -1;
			while (++x <= fractal->img.width)
				handle_pixel_julia(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_ptr,
		fractal->win_ptr,
		fractal->img.img_ptr,
		0,
		0);
	put_strings(fractal);
}
