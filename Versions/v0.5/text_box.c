/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_box.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:39:33 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/07 20:03:40 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	draw_a_box(t_box *box, t_fractal *fractal)
{
	int	init_y;

	init_y = box->from_y;
	box->from_x -= 1;
	while (++(box->from_x) < box->to_x && box->from_x < fractal->img.width)
	{
		box->from_y = init_y - 1;
		while (++(box->from_y) < box->to_y && box->from_y < fractal->img.height)
			my_mlx_pixel_put(&fractal->img, box->from_x, box->from_y, 0x000000);
	}
}
/*
static void	draw_color_box(t_fractal *fractal)
{


	int	x;
	int	y;

	x = -1;
	while (++x < 110 && x < fractal->img.width)
	{
		y = -1;
		while (++y < fractal->img.height)
			my_mlx_pixel_put(&fractal->img, x, y, 0x000000);
	}
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr,
		fractal->img.img_ptr, 0, 0);
}*/

void	draw_text_boxes(t_fractal *fractal)
{
	t_box	box;
/*
	box.from_x = 0;
	box.from_y = 0;
	box.to_x = 110;
	box.to_y = fractal->img.height;
	draw_a_box(&box, fractal);
*/
// v v v v box dynamique v v v v
	box.from_x = 0;
	box.from_y = 0;
	box.to_x = 220;
	box.to_y = 50;
	draw_a_box(&box, fractal);
// ^ ^ ^ ^ box dynamique ^ ^ ^ ^
	box.from_x = 0;
	box.from_y = fractal->img.height - 80;
	box.to_x = fractal->img.width;
	box.to_y = fractal->img.height;
	draw_a_box(&box, fractal);
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr,
		fractal->img.img_ptr, 0, 0);
}

