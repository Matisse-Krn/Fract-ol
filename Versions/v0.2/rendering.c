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

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	z.real = 0;
	z.imag = 0;
	c.real = scale_map(x, -2, 2, fractal->img.width) + fractal->shift_x;
	c.imag = scale_map(y, 2, -2, fractal->img.height) + fractal->shift_y;
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

void	fractal_rendering(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y <= fractal->img.height)
	{
		x = -1;
		while (++x <= fractal->img.width)
			handle_pixel(x, y, fractal);
	}
	mlx_put_image_to_window(fractal->mlx_ptr,
		fractal->win_ptr,
		fractal->img.img_ptr,
		0,
		0);
}
