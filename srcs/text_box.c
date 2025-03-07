/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_box.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:39:33 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 03:49:23 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Draws a filled black rectangle (box) within the image buffer.
 * Ensures the box does not exceed the image boundaries.
 * 
 * @param box A pointer to the box structure defining the area to draw.
 * @param fractal A pointer to the fractal structure.
 * 
 * Box parameters:
	- from_x, from_y: Top-left corner of the box.
	- to_x, to_y: Bottom-right corner of the box.
*/
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
 * Draws predefined text boxes at the top and bottom of the image.
 * Uses draw_a_box() to create the background for potential text display.
 * 
 * @param fractal A pointer to the fractal structure.
*/
void	draw_text_boxes(t_fractal *fractal)
{
	t_box	box;

	box.from_x = 0;
	box.from_y = 0;
	box.to_x = 220;
	box.to_y = 50;
	draw_a_box(&box, fractal);
	box.from_x = 0;
	box.from_y = fractal->img.height - 80;
	box.to_x = fractal->img.width;
	box.to_y = fractal->img.height;
	draw_a_box(&box, fractal);
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr,
		fractal->img.img_ptr, 0, 0);
}
